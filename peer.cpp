#include "peer.h"

void Peer::onProgressChanged()
{
    emit progressChanged(
        _transmissions.indexOf(
            dynamic_cast<Transmission*>(sender())));
}

void Peer::onFinished()
{
    int index = _transmissions.indexOf(dynamic_cast<Transmission*>(sender()));
    emit startRemove(index);
    _transmissions.remove(index);
    emit finishRemove();
}

void Peer::onNameChanged()
{
    emit nameChanged(
        _transmissions.indexOf(
            dynamic_cast<Transmission*>(sender())));
}

Peer::Peer(const QString &name, const QHostAddress &address, QObject* parent) :
    QObject(parent),
    _name(name),
    _address(address) {}

Peer::Peer(const Peer &other)
{
    _name = other.name();
    _address = other.address();
    _transmissions = other._transmissions;
}

Peer::~Peer()
{
}

QString Peer::name() const { return _name; }

QHostAddress Peer::address() const { return _address; }

void Peer::addTransmission(Transmission *transmission)
{
    connect(transmission, &Transmission::progressChanged, this, &Peer::onProgressChanged);
    connect(transmission, &Transmission::nameChanged, this, &Peer::onNameChanged);
    connect(transmission, &Transmission::finished, this, &Peer::onFinished);
    startAdd(_transmissions.size());
    _transmissions.append(transmission);
    finishAdd();
}

QVector<Transmission *>* Peer::transmissions() { return &_transmissions; }
