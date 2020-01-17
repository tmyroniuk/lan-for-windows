#include "peermodel.h"
#include "peerlist.h"

PeerList *PeerModel::list() const { return _list; }

void PeerModel::setList(PeerList *list)
{
    if(_list){
        _list->disconnect(this);
        delete _list;
    }

    _list = list;

    connect(_list, &PeerList::startRefresh, this, [this](){ beginResetModel(); });
    connect(_list, &PeerList::finishRefresh, this, [this](){ endResetModel(); });
}

PeerModel::PeerModel(QObject *parent)
    : QAbstractListModel(parent),
      _list(nullptr) {}

PeerModel::~PeerModel() { delete _list; }

int PeerModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return _list->data().size();
}

QVariant PeerModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    switch(role){
    case NameRole:
        return _list->data().at(index.row()).name();
    case AddressRole:
        return _list->data().at(index.row()).address().toString();
    }
    return QVariant();
}

QHash<int, QByteArray> PeerModel::roleNames() const
{
    QHash<int, QByteArray> hash;
    hash[NameRole] = "name";
    hash[AddressRole] = "address";
    return hash;
}
