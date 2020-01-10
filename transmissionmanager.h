#ifndef TRANSMISSIONMANAGER_H
#define TRANSMISSIONMANAGER_H

#include <QObject>
#include <QHostAddress>

#include "recieverserver.h"
#include "senderthread.h"

class TransmissionManager : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString data READ data WRITE updateData NOTIFY dataRecieved)

public:
    explicit TransmissionManager(QObject *parent = nullptr);

    ~TransmissionManager();

    QString data();

public slots:
    void send(const QHostAddress& address, const quint16& port);

private slots:
    void updateData(const QString& data);

signals:
    void dataRecieved();

private:
    RecieverServer* _listener;
    QString _data;
};

#endif // TRANSMISSIONMANAGER_H
