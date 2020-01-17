#ifndef PEERLIST_H
#define PEERLIST_H

#include <QObject>
#include <QVector>

#include "searcher.h"
#include "peer.h"

class PeerList : public QObject{
    Q_OBJECT

    Searcher _searcher;
    QVector<Peer> _list;

public:
    explicit PeerList(QObject *parent = nullptr);

    QVector<Peer> data() const;

public slots:
    void refresh();

signals:
    void startRefresh();

    void finishRefresh();
};

#endif // PEERLIST_H
