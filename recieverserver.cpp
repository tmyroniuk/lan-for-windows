#include "recieverserver.h"

RecieverServer::RecieverServer(QObject *parent):
    QTcpServer(parent) {}

void RecieverServer::incomingConnection(qintptr socketDescriptor)
{
    auto thread = new QThread;
    auto reciever = new Reciever(socketDescriptor);
    reciever->moveToThread(thread);
    connect(reciever, &Reciever::finished, thread, &QThread::quit);
    connect(reciever, &Reciever::peerConnected, this, &RecieverServer::onPeerConnected);
    connect(thread, &QThread::finished, thread, &QObject::deleteLater);
    connect(thread, &QThread::finished, reciever, &QObject::deleteLater);
    connect(thread, &QThread::started, reciever, &Reciever::start);
    thread->start();
}

void RecieverServer::onPeerConnected(const QHostAddress& host)
{
    emit newConnection(dynamic_cast<Transmission*>(sender()), host);
}
