#include "recieverthread.h"

RecieverThread::RecieverThread(qintptr socketDescriptor, QObject *parent):
    QThread(parent),
    _socketDescriptor(socketDescriptor) {}

void RecieverThread::run()
{
    QTcpSocket socket;
    QString data;


    if(!socket.setSocketDescriptor(_socketDescriptor)){
        emit error(socket.error(), socket.errorString());
        return;
    }

    QDataStream stream(&socket);
    stream.setVersion(QDataStream::Qt_5_12);

    do{
        if (!socket.waitForReadyRead()) {
           emit error(socket.error(), socket.errorString());
           return;
       }

       stream.startTransaction();
       stream >> data;
    } while(!stream.commitTransaction());

    emit recieved(data);
}
