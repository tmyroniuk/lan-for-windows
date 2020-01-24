#ifndef PEERLIST_H
#define PEERLIST_H

#include <QObject>
#include <QVector>

#include "searcher.h"
#include "peer.h"
#include "transmissionmanager.h"

class PeerList : public QObject{
    Q_OBJECT

    TransmissionManager _trManager;
    Searcher _searcher;
    QVector<Peer> _list;

public:
    explicit PeerList(QObject *parent = nullptr);

    QVector<Peer> data() const;

public slots:
    void refresh();

    void clear();

signals:
    void startRefresh();

    void finishRefresh();
};

#endif // PEERLIST_H
