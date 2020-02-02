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

class TransmissionManager : public QObject
{
    Q_OBJECT

    Searcher _searcher;
    RecieverServer* _listener;
    QVector<Peer*>* _list;

public:
    explicit TransmissionManager(QObject *parent = nullptr);

    QVector<Peer*>* peerList();

    ~TransmissionManager();

    void send(int i, const QUrl& filePath);

public slots:
    void refresh();

private slots:
    void onNewConnection(Transmission* transmission, const QHostAddress& address);

    void onFinished(const bool& status, const QString& fileName, const QString& errorString);

signals:
    void complete(QString);

    void error(QString, QString);

    void startRefresh();

    void finishRefresh();

    void dataChanged(int);
};

#endif // TRANSMISSIONMANAGER_H
