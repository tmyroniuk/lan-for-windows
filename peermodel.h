#ifndef PEERMODEL_H
#define PEERMODEL_H

#include <QAbstractListModel>

class PeerList;

class PeerModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(PeerList* list READ list WRIGHT setList)

    PeerList* _list;

public:
    explicit PeerModel(QObject *parent = nullptr);

    ~PeerModel() override;

    enum{
        NameRole = Qt::UserRole,
        AddressRole
    };

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    QHash<int, QByteArray> roleNames() const override;

    PeerList* list() const;

    void setList(PeerList *list);
};

#endif // PEERMODEL_H
