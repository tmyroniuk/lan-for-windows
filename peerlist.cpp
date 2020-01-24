#include "peerlist.h"

#include <QTimer>

#include "globals.h"

PeerList::PeerList(QObject *parent) :
    QObject(parent) {}

QVector<Peer> PeerList::data() const { return _list ;}

void PeerList::refresh()
{
    _list.clear();

    emit startRefresh();
    connect(&_searcher, &Searcher::answerRecieved, this,
        [this](const QString& name, const QHostAddress& address){ _list.append(Peer(name, address)); });

    _searcher.send();

    QTimer::singleShot(REFRESH_TIME, [this]() {
        _searcher.disconnect(this);
        emit finishRefresh();
    });
}

void PeerList::clear()
{
    emit startRefresh();
    _list.clear();
    emit finishRefresh();
}
