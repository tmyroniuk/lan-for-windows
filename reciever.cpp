#include "reciever.h"

Reciever::Reciever(qintptr socketDescriptor, QObject *parent) :
    QObject(parent),
    _socketDescriptor(socketDescriptor){}

void Reciever::start() {
    QFile file;
    QTcpSocket socket;
    QString fileName;
    QByteArray block;
    qint64 fileSize;
    qint64 currentSize = 0;

    //setup sockret
    if(!socket.setSocketDescriptor(_socketDescriptor)){
        onError(file, socket);
        return;
    }
    //get file name and size
    QDataStream readStream(&socket);
    readStream.setVersion(QDataStream::Qt_5_12);
    if(!socket.waitForReadyRead(TIMEOUT)){
        onError(file, socket);
        return;
    }
    readStream >> fileName;
    readStream >> fileSize;
    file.setFileName(SAVING_PATH + fileName);
    //get file
    if(file.open(QIODevice::WriteOnly)){
        while(currentSize < fileSize){
            if(!socket.waitForReadyRead(TIMEOUT)){
                onError(file, socket);
                return;
            }
            block = socket.read(BLOCK_LEN);
            file.write(block);
            currentSize += block.size();
        }
        file.close();
        socket.disconnectFromHost();
        socket.waitForDisconnected(TIMEOUT);
    }
    else{
        onError(file, socket);
        return;
    }
    qDebug() << "recieving finished" << SAVING_PATH + fileName << QThread::currentThread();
    emit finished(true);
}

void Reciever::onError(QFile& file, QTcpSocket& socket) {
    qDebug() <<"file" << file.error() << file.errorString();
    qDebug() <<"socket" << socket.error() << socket.errorString();
    file.remove();
    socket.disconnectFromHost();
    emit finished(false);
}
