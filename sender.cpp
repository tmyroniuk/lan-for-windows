#include "sender.h"

Sender::Sender(QHostAddress host, const QUrl filePath, QObject *parent) :
    QObject(parent),
    _host(host),
    _filePath(filePath) {}

void Sender::start()
{
    QTcpSocket socket;
    QFile file(_filePath.toLocalFile());
    if(file.open(QIODevice::ReadOnly)){
        socket.connectToHost(_host, TCP_PORT);
        if (!socket.waitForConnected(TIMEOUT)) {
            onError(file, socket);
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
            if(!socket.waitForBytesWritten(TIMEOUT)){
                onError(file, socket);
                return;
            }
            socket.write(block);
        }
        file.close();
        socket.disconnectFromHost();
        socket.waitForDisconnected(TIMEOUT);
    }
    else{
        onError(file, socket);
        return;
    }
    qDebug() << "sending finised" << file.fileName() << QThread::currentThread();
    emit finished(true);
}

void Sender::onError(QFile& file, QTcpSocket& socket)
{
    qDebug() <<"file" << file.error() << file.errorString();
    qDebug() <<"socket" << socket.error() << socket.errorString();
    file.close();
    socket.disconnectFromHost();
    emit finished(false);
}
