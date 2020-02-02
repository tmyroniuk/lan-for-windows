#ifndef PEER_H
#define PEER_H

#include <QObject>
#include <QVector>
#include <QHostAddress>

#include "transmission.h"

class Peer : public QObject
{
    Q_OBJECT

    QString _name;
    QHostAddress _address;
    QVector<Transmission*> _transmissions;

private slots:
    void onProgressChanged();

    void onFinished();

    void onNameChanged();

signals:
    void nameChanged(int);

    void progressChanged(int);

    void startRemove(int);

    void finishRemove();

    void startAdd(int);

    void finishAdd();

public:    
    Peer(const QString& name, const QHostAddress& address, QObject* parent = nullptr);

    Peer() = default;

    Peer(const Peer& other);

    ~Peer();

    QString name() const;

    QHostAddress address() const;

    void addTransmission(Transmission* transmission);

    QVector<Transmission *>* transmissions();
};

#endif // PEER_H
