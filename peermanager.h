#ifndef PEERMANAGER_H
#define PEERMANAGER_H

#include <QObject>

#include "searcher.h"

class PeerManager : public QObject
{
    Q_OBJECT
public:
    explicit PeerManager(QObject *parent = nullptr);

    ~PeerManager();

public slots:
    void refresh();

private slots:
    void newPeer(QString hostName, QHostAddress address);

private:
    Searcher* _searcher;
};

#endif // PEERMANAGER_H
