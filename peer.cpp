#include "peer.h"

Peer::Peer(const QString &name, const QHostAddress &address) :
    _name(name),
    _address(address) {}

Peer::Peer(const Peer &other)
{
    _name = other.name();
    _address = other.address();
}

QString Peer::name() const { return _name; }

QHostAddress Peer::address() const { return _address; }

void Peer::send(QUrl fileName) { TransmissionManager::send(_address, fileName); }

void Peer::operator =(const Peer &other)
{
    _name = other.name();
    _address = other.address();
}
