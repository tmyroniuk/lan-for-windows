#include "transmissionmanager.h"
#include "globals.h"

TransmissionManager::TransmissionManager(QObject *parent) :
    QObject(parent),
    _listener(new RecieverServer(this))
{
    connect(_listener, SIGNAL(dataRecieved(QString)), this, SLOT(updateData(QString)));
    _listener->listen(QHostAddress::Any, TCP_PORT);
}

TransmissionManager::~TransmissionManager() {delete _listener;}

QString TransmissionManager::data() {return _data;}

void TransmissionManager::send(const QHostAddress& address, const quint16& port)
{
    auto thread = new SenderThread(address, port, _data, this);
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    thread->start();
}

void TransmissionManager::updateData(const QString& data) {_data = data;}
