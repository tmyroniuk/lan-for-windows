#include "peermodel.h"
#include <QVariant>

PeerModel::PeerModel(QObject *parent)
    : QAbstractListModel(parent),
      _manager(nullptr) {}

PeerModel::~PeerModel() { delete _manager; }

int PeerModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid() || !_manager)
        return 0;

    return _manager->peerList()->size();
}

QVariant PeerModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || !_manager)
        return QVariant();

    switch(role){
    case NameRole:
        return _manager->peerList()->value(index.row())->name();
    case AddressRole:
        return _manager->peerList()->value(index.row())->address().toString();
    case PeerRole:
        return QVariant::fromValue(_manager->peerList()->value(index.row()));
    }
    return QVariant();
}

QHash<int, QByteArray> PeerModel::roleNames() const
{
    QHash<int, QByteArray> hash;
    hash[NameRole] = "name";
    hash[AddressRole] = "address";
    hash[SendRole] = "send";
    hash[PeerRole] = "peer";
    return hash;
}

bool PeerModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid() || !_manager)
        return false;

    switch(role){
    case SendRole:
        _manager->send(index.row(), value.toUrl());
        emit dataChanged(index, index, QVector<int>() << PeerRole);
        return true;
    }
    return false;
}

TransmissionManager *PeerModel::manager() const { return _manager; }

void PeerModel::setManager(TransmissionManager *manager)
{
    beginResetModel();

    if(_manager) delete _manager;
    _manager = manager;

    connect(_manager, &TransmissionManager::startRefresh, this, [this](){ beginResetModel(); });
    connect(_manager, &TransmissionManager::finishRefresh, this, [this](){ endResetModel(); });

    endResetModel();
}
