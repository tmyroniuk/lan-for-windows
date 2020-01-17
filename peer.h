#ifndef PEER_H
#define PEER_H

#include "transmissionmanager.h"

class Peer
{
    QString _name;
    QHostAddress _address;

public:    
    Peer(const QString& name, const QHostAddress& address);

    QString name() const;

    QHostAddress address() const;

    void send(QUrl fileName);
};

#endif // PEER_H
