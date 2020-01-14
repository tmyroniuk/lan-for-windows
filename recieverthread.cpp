#include "recieverthread.h"

RecieverThread::RecieverThread(qintptr socketDescriptor, QObject *parent):
    QThread(parent),
    _socketDescriptor(socketDescriptor) {}

void RecieverThread::run()
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

    do {
        readStream.startTransaction();
        readStream >> fileName;
        readStream >> fileSize;
        qDebug() << fileName << fileSize;
    } while(!readStream.commitTransaction());

    QByteArray block;
    QFile file(SAVING_PATH + fileName);
    if(file.open(QIODevice::WriteOnly)){
        while(currentSize < fileSize){
            while(!readStream.commitTransaction()){
                readStream.startTransaction();
                readStream >> block;
            }
            file.write(block);
            currentSize += block.size();
            qDebug() << currentSize << fileSize << "\n";
        }
    }
    else{
        qDebug() << "reciever cant open" << SAVING_PATH + fileName;
        emit fileError(file.error(), file.errorString());
    }
}
