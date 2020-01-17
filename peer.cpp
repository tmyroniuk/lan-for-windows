#include "peer.h"

Peer::Peer(const QString &name, const QHostAddress &address) :
    _name(name),
    _address(address) {}

QString Peer::name() const { return _name; }

QHostAddress Peer::address() const { return _address; }

void Peer::send(QUrl fileName) { TransmissionManager::send(_address, fileName); }
