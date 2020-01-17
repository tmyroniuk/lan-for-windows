#include "recieverserver.h"

RecieverServer::RecieverServer(QObject *parent):
    QTcpServer(parent) {}

void RecieverServer::incomingConnection(qintptr socketDescriptor)
{
    auto thread = new QThread;
    auto reciever = new Reciever(socketDescriptor);
    reciever->moveToThread(thread);
    connect(reciever, &Reciever::finished, thread, &QThread::quit);
    connect(thread, &QThread::finished, thread, &QObject::deleteLater);
    connect(thread, &QThread::finished, reciever, &QObject::deleteLater);
    connect(thread, &QThread::started, reciever, &Reciever::start);
    thread->start();
}
