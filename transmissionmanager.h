#ifndef TRANSMISSIONMANAGER_H
#define TRANSMISSIONMANAGER_H

#include <QObject>
#include <QThread>
#include <QTimerEvent>
#include <QUrl>

#include "recieverserver.h"
#include "sender.h"

class TransmissionManager : public QObject
{
    Q_OBJECT

public:
    explicit TransmissionManager(QObject *parent = nullptr);

    ~TransmissionManager();

public slots:
    void send(const QHostAddress& address, const QUrl& path);

    void sendToLaptop(const QUrl& path);

private:
    RecieverServer* _listener;
};

#endif // TRANSMISSIONMANAGER_H
