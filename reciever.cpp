#include "reciever.h"

Reciever::Reciever(qintptr socketDescriptor, QObject *parent) :
    Transmission(parent),
    _socketDescriptor(socketDescriptor){}

void Reciever::start() {
    QFile file;
    QTcpSocket socket;
    qint64 fileSize;

    qint64 currentSize = 0;
    QByteArray block;
    QDataStream readStream(&socket);
    readStream.setVersion(QDataStream::Qt_5_12);

    //setup socket
    if(!socket.setSocketDescriptor(_socketDescriptor)){
        onError(file, socket);
        return;
    }
    emit peerConnected(QHostAddress(socket.peerAddress().toIPv4Address()));

    //get file name and size
    socket.waitForReadyRead(TIMEOUT);
    readStream >> _fileName;
    readStream >> fileSize;
    file.setFileName(SAVING_PATH + _fileName);
    emit nameChanged();

    //create file
    if(!file.open(QIODevice::WriteOnly)){
        onError(file, socket);
        return;
    }

    //recieve data
    while(currentSize < fileSize){
        socket.waitForReadyRead(TIMEOUT);
        if(checkForError(file, socket)){
            file.remove();
            return;
        }
        block = socket.read(BLOCK_LEN);
        file.write(block);
        currentSize += block.size();
        _progress = 1.0 * currentSize / fileSize;
        emit progressChanged();
    }

    //Disconnect and close file
    file.close();
    socket.disconnectFromHost();
    socket.waitForDisconnected(TIMEOUT);

    qDebug() << "recieving finished" << SAVING_PATH + _fileName;
    emit finished(true, _fileName);
}
