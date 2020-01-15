#ifndef TRANSMISSIONMANAGER_H
#define TRANSMISSIONMANAGER_H

#include <QObject>
#include <QThread>

#include "recieverserver.h"
#include "sender.h"

class TransmissionManager : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString data READ data WRITE setData NOTIFY dataChanged)

public:
    explicit TransmissionManager(QObject *parent = nullptr);

    ~TransmissionManager();

    QString data();

public slots:
    void send(const QHostAddress& address);

    void sendToLaptop();

private slots:
    void setData(const QString& data);

signals:
    void dataChanged();

private:
    RecieverServer* _listener;
    QString _data;
};

#endif // TRANSMISSIONMANAGER_H
