#include "reciever.h"

Reciever::Reciever(qintptr socketDescriptor, QObject *parent) :
    QObject(parent),
    _socketDescriptor(socketDescriptor) {}

void Reciever::recieveTransmission()
{
    QTcpSocket socket;
    QString fileName;
    qint64 fileSize;
    qint64 currentSize = 0;
    if(!socket.setSocketDescriptor(_socketDescriptor)){
        emit error(socket.error(), socket.errorString());
        return;
    }

    QDataStream readStream(&socket);
    readStream.setVersion(QDataStream::Qt_5_12);

    socket.waitForReadyRead();
    readStream >> fileName;
    readStream >> fileSize;

    QByteArray block;
    QFile file(SAVING_PATH + fileName);
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
