#ifndef PEER_H
#define PEER_H

#include <QObject>
#include <QVector>

#include "transmissionmanager.h"

class Peer : QObject
{
    Q_OBJECT

    QString _name;
    QHostAddress _address;
    QVector<Transmission*> _transmissions;
signals:
    void progressChanged(int);

    void

public:    
    Peer(const QString& name, const QHostAddress& address, QObject* parent = nullptr);

    Peer() = default;

    //Peer(const Peer& other);

    QString name() const;

    QHostAddress address() const;

    void send(QUrl fileName);

    QVector<Transmission *> transmissions() const;
};

#endif // PEER_H
