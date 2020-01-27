#include "transmissionmanager.h"
#include "globals.h"
#include "peer.h"

TransmissionManager::TransmissionManager(QObject *parent) :
    QObject(parent),
    _listener(new RecieverServer(this))
{
    _listener->listen(QHostAddress::Any, TCP_PORT);
}

TransmissionManager::~TransmissionManager() {delete _listener;}

void TransmissionManager::send(Peer& peer, const QUrl& path)
{
    qDebug() << path;
    auto thread = new QThread;
    auto sender = new Sender(peer.address(), path);
    sender->moveToThread(thread);
    peer.addTransmission(sender);
    connect(sender, &Sender::finished, thread, &QThread::quit);
    connect(thread, &QThread::finished, thread, &QObject::deleteLater);
    connect(thread, &QThread::started, sender, &Sender::start);
    thread->start();
}
