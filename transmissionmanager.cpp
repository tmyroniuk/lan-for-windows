#include "transmissionmanager.h"
#include "globals.h"

TransmissionManager::TransmissionManager(QObject *parent) :
    QObject(parent),
    _listener(new RecieverServer(this))
{
    _listener->listen(QHostAddress::Any, TCP_PORT);
}

TransmissionManager::~TransmissionManager() {delete _listener;}

void TransmissionManager::send(const QHostAddress& address, const QUrl& path)
{
    qDebug() << path;
    auto thread = new QThread;
    auto sender = new Sender(address, path);
    sender->moveToThread(thread);
    connect(thread, &QThread::finished, thread, &QObject::deleteLater);
    connect(thread, &QThread::finished, sender, &QObject::deleteLater);
    connect(thread, &QThread::started, sender, &Sender::startTransmission);
    thread->start();
}

void TransmissionManager::sendToLaptop(const QUrl& path)
{
    send(QHostAddress("192.168.1.242"), path);
}
