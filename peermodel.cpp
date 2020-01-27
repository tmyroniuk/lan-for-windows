#include "peermodel.h"

PeerModel::PeerModel(QObject *parent)
    : QAbstractListModel(parent),
      _list(nullptr) {}

PeerModel::~PeerModel() { delete _list; }

int PeerModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid() || !_list)
        return 0;

    return _list->data().size();
}

QVariant PeerModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || !_list)
        return QVariant();

    switch(role){
    case NameRole:
        return _list->data()[index.row()].name();
    case AddressRole:
        return _list->data()[index.row()].address().toString();
    }
    return QVariant();
}

QHash<int, QByteArray> PeerModel::roleNames() const
{
    QHash<int, QByteArray> hash;
    hash[NameRole] = "name";
    hash[AddressRole] = "address";
    hash[SendRole] = "send";
    return hash;
}

bool PeerModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid() || !_list)
        return false;

    switch(role){
    case SendRole:
        _list->sendTo(index.row(), value.toUrl());
        return true;
    }
    return false;
}

PeerList *PeerModel::list() const { return _list; }

void PeerModel::setList(PeerList *list)
{
    beginResetModel();

    if(_list) delete _list;
    _list = list;

    connect(_list, &PeerList::startRefresh, this, [this](){ beginResetModel(); });
    connect(_list, &PeerList::finishRefresh, this, [this](){ endResetModel(); });

    endResetModel();
}
