#include "recieverserver.h"


RecieverServer::RecieverServer(QObject *parent):
    QTcpServer(parent) {}

void RecieverServer::incomingConnection(qintptr socketDescriptor)
{
    auto thread = new RecieverThread(socketDescriptor, this);
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    thread->start();
}
