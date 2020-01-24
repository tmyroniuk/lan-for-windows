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
    QDataStream readStream(&socket);
    readStream.setVersion(QDataStream::Qt_5_12);

    //setup socket
    if(!socket.setSocketDescriptor(_socketDescriptor)){
        onError(file, socket);
        return;
    }

    //get file name and size
    socket.waitForReadyRead(TIMEOUT);
    readStream >> fileName;
    readStream >> fileSize;
    file.setFileName(SAVING_PATH + fileName);

    //create file
    if(!file.open(QIODevice::WriteOnly)){
        onError(file, socket);
        return;
    }

    //recieve data
    while(currentSize < fileSize){
        socket.waitForReadyRead(TIMEOUT);
        if(file.error() != QFile::NoError || socket.error() != QTcpSocket::UnknownSocketError){
            onError(file, socket);
            return;
        }
        file.write(socket.read(BLOCK_LEN));
        currentSize += block.size();
    }

    //Disconnect and close file
    file.close();
    socket.disconnectFromHost();
    socket.waitForDisconnected(TIMEOUT);

    qDebug() << "recieving finished" << SAVING_PATH + fileName << QThread::currentThread();
    emit finished(true);
}

void Reciever::onError(QFile& file, QTcpSocket& socket) {
    qDebug() <<"file" << file.error() << file.errorString();
    qDebug() <<"socket" << socket.error() << socket.errorString();
    file.remove();
    if(socket.state() == QTcpSocket::ConnectedState) socket.disconnectFromHost();
    emit finished(false);
}
