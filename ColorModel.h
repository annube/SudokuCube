#ifndef COLORMODEL_H
#define COLORMODEL_H

#include <QAbstractListModel>

class ColorModel : public QAbstractListModel
{
  Q_OBJECT

public:
  enum CustomRoles
  {
    ColorRole=Qt::UserRole+1,
  };
  explicit ColorModel(QObject *parent = nullptr);

  // Header:
  QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

  int rowCount(const QModelIndex &parent = QModelIndex()) const override;

  QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private:

  // QAbstractItemModel interface
public:
  virtual QHash<int, QByteArray> roleNames() const override;
};

#endif // COLORMODEL_H
