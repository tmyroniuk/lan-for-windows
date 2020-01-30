#ifndef TRANSMISSIONMANAGER_H
#define TRANSMISSIONMANAGER_H

#include <QObject>
#include <QThread>
#include <QTimerEvent>
#include <QUrl>

#include "recieverserver.h"
#include "sender.h"
#include "searcher.h"
#include "peer.h"

class Peer;

class TransmissionManager : public QObject
{
    Q_OBJECT

    Searcher _searcher;
    RecieverServer* _listener;
    QVector<Peer*> _list;

public:
    explicit TransmissionManager(QObject *parent = nullptr);

    QVector<Peer*>* peerList();

    ~TransmissionManager();

    void send(int i, const QUrl& filePath);

public slots:
    void refresh();

    void clear();

private slots:
    void onComplete(QString fileName, QString hostName, QHostAddress address);

    void onError(QString fileName, QString hostName, QHostAddress address, QString errorString);

signals:
    void startRefresh();

    void finishRefresh();
};

#endif // TRANSMISSIONMANAGER_H
