#include "sender.h"

Sender::Sender(QHostAddress host, const QUrl filePath, QObject *parent) :
    QObject(parent),
    _host(host),
    _filePath(filePath) {}

void Sender::start()
{
    QTcpSocket socket;
    QFile file(_filePath.toLocalFile());

    //Open file
    if(!file.open(QIODevice::ReadOnly))
        onError(file, socket);

    //Connect
    socket.connectToHost(_host, TCP_PORT);
    if (!socket.waitForConnected(TIMEOUT))
        onError(file, socket);

    //Sending data
    QByteArray block;
    QDataStream wrightStream(&block, QIODevice::WriteOnly);
    wrightStream.setVersion(QDataStream::Qt_5_12);
    wrightStream << _filePath.fileName();
    wrightStream << file.size();
    socket.write(block);

    //Sending file
    while(!file.atEnd()){
        block = file.read(BLOCK_LEN);
        if(file.error() != QFile::NoError || socket.error() != QTcpSocket::UnknownSocketError)
            onError(file, socket);
        while(socket.bytesToWrite() > MAX_BOOFER_SIZE){
            socket.waitForBytesWritten(TIMEOUT);
            if(file.error() != QFile::NoError || socket.error() != QTcpSocket::UnknownSocketError)
                onError(file, socket);
        }
        socket.write(block);
    }

    //Disconnect and close file
    file.close();
    socket.disconnectFromHost();
    socket.waitForDisconnected(TIMEOUT);

    qDebug() << "sending finised" << file.fileName() << QThread::currentThread();
    emit finished(true);
}

void Sender::onError(QFile& file, QTcpSocket& socket)
{
    qDebug() <<"file" << file.error() << file.errorString();
    qDebug() <<"socket" << socket.error() << socket.errorString();
    if(file.isOpen()) file.close();
    if(socket.state() == QTcpSocket::ConnectedState) socket.disconnectFromHost();
    emit finished(false);
    QThread::currentThread()->wait();
}
