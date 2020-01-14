#include "transmissionmanager.h"
#include "globals.h"

TransmissionManager::TransmissionManager(QObject *parent) :
    QObject(parent),
    _listener(new RecieverServer(this))
{
    _listener->listen(QHostAddress::Any, TCP_PORT);
}

TransmissionManager::~TransmissionManager() {delete _listener;}

QString TransmissionManager::data() {return _data;}

void TransmissionManager::send(const QHostAddress& address)
{
    auto thread = new SenderThread(address, _data, this);
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    thread->start();
}

void TransmissionManager::sendToLaptop()
{
    send(QHostAddress("192.168.1.242"));
}

void TransmissionManager::setData(const QString& data)
{
    _data = data;
    emit dataChanged();
}
