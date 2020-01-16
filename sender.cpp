#include "sender.h"

Sender::Sender(QHostAddress host, const QUrl filePath, QObject *parent) :
    QObject(parent),
    _filePath(filePath),
    _host(host) {}

void Sender::startTransmission()
{
    QFile file(_filePath.toLocalFile());
    connect(&file, &QFileDevice::error, [this, &file](){
        emit fileError(file.error(), file.errorString());
        QThread::currentThread()->quit();
        QThread::currentThread()->wait();});

    if(file.open(QIODevice::ReadOnly)){
        QTcpSocket socket;
        connect(&socket, QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error), [this, &socket](){
            emit socketError(socket.error(), socket.errorString());
            QThread::currentThread()->quit();
            QThread::currentThread()->wait();});

        socket.connectToHost(_host, TCP_PORT);
        if (!socket.waitForConnected()) {
            emit socketError(socket.error(), socket.errorString());
            return;
        }
        //sending data
        QByteArray block;
        QDataStream wrightStream(&block, QIODevice::WriteOnly);
        wrightStream.setVersion(QDataStream::Qt_5_12);
        wrightStream << _filePath.fileName();
        wrightStream << file.size();
        socket.write(block);
        //Sending file
        while(!file.atEnd()){
            block = file.read(BLOCK_LEN);
            socket.waitForBytesWritten();
            socket.write(block);
        }
        socket.disconnectFromHost();
        socket.waitForDisconnected();
        file.close();
    }
    else {
        qDebug() << "sender cant open";
        emit fileError(file.error(), file.errorString());
    }
    qDebug() << "sending finised" << _filePath << QThread::currentThread();
    QThread::currentThread()->quit();
}
