#ifndef TRANSMISSIONMODEL_H
#define TRANSMISSIONMODEL_H

#include <QAbstractListModel>

#include "peer.h"

class TransmissionModel : public QAbstractListModel
{
    Q_OBJECT

    Peer* _peer;

public:
    enum{
        NameRole = Qt::UserRole,
        ProgressRole
    };

    explicit TransmissionModel(QObject *parent = nullptr);

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    QHash<int, QByteArray> roleNames() const override;

    Peer *peer() const;

    void setPeer(Peer *peer);
};

#endif // TRANSMISSIONMODEL_H
