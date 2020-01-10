#include "peermanager.h"

PeerManager::PeerManager(QObject *parent) :
    QObject(parent),
    _searcher(new Searcher(this))
{
    connect (_searcher, SIGNAL(answerRecieved(QString, QHostAddress)), this, SLOT(newPeer(QString, QHostAddress)));
}

PeerManager::~PeerManager()
{
    delete _searcher;
}

void PeerManager::refresh()
{
    _searcher->send();
}

void PeerManager::newPeer(QString hostName, QHostAddress address)
{
    qDebug()<< hostName << address.toString();
}
