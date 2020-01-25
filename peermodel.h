#ifndef PEERMODEL_H
#define PEERMODEL_H

#include <QAbstractListModel>

#include "peerlist.h"

class PeerModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(PeerList* list READ list WRITE setList)

    PeerList* _list;

public:
    explicit PeerModel(QObject *parent = nullptr);

    ~PeerModel();

    enum{
        NameRole = Qt::UserRole,
        AddressRole,
        SendRole
    };

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    QHash<int, QByteArray> roleNames() const override;

    bool setData(const QModelIndex &index, const QVariant &value, int role) override;

    PeerList* list() const;

    void setList(PeerList* list);
};

#endif // PEERMODEL_H
