#include "transmissionmodel.h"

TransmissionModel::TransmissionModel(QObject *parent) :
    QAbstractListModel(parent),
    _peer(nullptr) {}

int TransmissionModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid() || !_peer)
        return 0;

    return _peer->transmissions()->size();
}

QVariant TransmissionModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    switch(role){
    case NameRole:
        return _peer->transmissions()->value(index.row())->fileName();
    case ProgressRole:
        return _peer->transmissions()->value(index.row())->progress();
    }

    return QVariant();
}

QHash<int, QByteArray> TransmissionModel::roleNames() const
{
    QHash<int, QByteArray> hash;
    hash[NameRole] = "fileName";
    hash[ProgressRole] = "progress";
    return hash;
}

Peer *TransmissionModel::peer() const { return _peer; }

void TransmissionModel::setPeer(Peer *peer) {
    beginResetModel();

    if(_peer) _peer->disconnect(this);
    _peer = peer;

    connect(_peer, &Peer::progressChanged, this, [this](int i){
        emit dataChanged(index(i), index(i), QVector<int>() << ProgressRole);
    });

    connect(_peer, &Peer::nameChanged, this, [this](int i){
        emit dataChanged(index(i), index(i), QVector<int>() << NameRole);
    });

    connect(_peer, &Peer::startRemove, this, [this](int i){
        beginRemoveRows(QModelIndex(), i, i);
    });

    connect(_peer, &Peer::finishRemove, this, [this](){
        endRemoveRows();
    });

    endResetModel();
}
