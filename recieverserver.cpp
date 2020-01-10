#include "recieverserver.h"


RecieverServer::RecieverServer(QObject *parent):
    QTcpServer(parent) {}

void RecieverServer::incomingConnection(qintptr socketDescriptor)
{
    auto thread = new RecieverThread(socketDescriptor, this);
    connect(this, SIGNAL(dataRecieved(QString)), thread, SIGNAL(recieved(QString)));
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    thread->start();
}
