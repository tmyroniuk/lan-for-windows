#ifndef PEERMODEL_H
#define PEERMODEL_H

#include <QAbstractListModel>

#include "transmissionmanager.h"

class PeerModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(TransmissionManager* manager READ manager WRITE setManager)

    TransmissionManager* _manager;

public:
    explicit PeerModel(QObject *parent = nullptr);

    enum{
        NameRole = Qt::UserRole,
        AddressRole,
        SendRole,
        PeerRole
    };

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    QHash<int, QByteArray> roleNames() const override;

    bool setData(const QModelIndex &index, const QVariant &value, int role) override;

    TransmissionManager* manager() const;

    void setManager(TransmissionManager* manager);
};

#endif // PEERMODEL_H
