#include "peer.h"

Peer::Peer(const QString &name, const QHostAddress &address, QObject* parent) :
    QObject(parent),
    _name(name),
    _address(address) {}
/*
Peer::Peer(const Peer &other)
{
    _name = other.name();
    _address = other.address();
    _transmissions = other._transmissions;
}
*/
QString Peer::name() const { return _name; }

QHostAddress Peer::address() const { return _address; }

void Peer::send(QUrl fileName) { TransmissionManager::send(_address, fileName); }

QVector<Transmission *> Peer::transmissions() const { return _transmissions; }
