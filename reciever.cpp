#include "reciever.h"

Reciever::Reciever(qintptr socketDescriptor, QObject *parent) :
    QObject(parent),
    _socketDescriptor(socketDescriptor) {}

void Reciever::recieveTransmission()
{
    QTcpSocket socket;
    connect(&socket, QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error), [this, &socket](){
        emit socketError(socket.error(), socket.errorString());
        QThread::currentThread()->quit();
        QThread::currentThread()->wait();});

    QString fileName;
    qint64 fileSize;
    qint64 currentSize = 0;
    if(!socket.setSocketDescriptor(_socketDescriptor)){
        emit socketError(socket.error(), socket.errorString());
        return;
    }

    QDataStream readStream(&socket);
    readStream.setVersion(QDataStream::Qt_5_12);

    socket.waitForReadyRead();
    readStream >> fileName;
    readStream >> fileSize;

    QByteArray block;
    QFile file(SAVING_PATH + fileName);
    connect(&file, &QFileDevice::error, [this, &file](){
        emit fileError(file.error(), file.errorString());
        QThread::currentThread()->quit();
        QThread::currentThread()->wait();});
    if(file.open(QIODevice::WriteOnly)){
        while(currentSize < fileSize){
            socket.waitForReadyRead();
            block = socket.read(BLOCK_LEN);
            file.write(block);
            currentSize += block.size();
        }
        socket.disconnectFromHost();
        socket.waitForDisconnected();
        file.close();
    }
    else{
        qDebug() << "reciever cant open" << SAVING_PATH + fileName;
        emit fileError(file.error(), file.errorString());
    }
    qDebug() << "recieving finished" << SAVING_PATH + fileName << QThread::currentThread();
    QThread::currentThread()->quit();
}
