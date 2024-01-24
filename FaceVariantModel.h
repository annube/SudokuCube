#ifndef FACEVARIANTMODEL_H
#define FACEVARIANTMODEL_H

#include <QAbstractListModel>
#include <FaceCoords.h>
#include <QtQml/qqmlregistration.h>

class FaceVariantModel : public QAbstractListModel
{
  Q_OBJECT
  QML_ELEMENT
public:
  explicit FaceVariantModel(int face, QObject *parent = nullptr);

  // QAbstractItemModel interface
public:
  enum Roles
  {
    VariantPossible = Qt::UserRole+1,
    ModelIndex,
  };
  enum VariantState
  {
    POSSIBLE,
    IMPOSSIBLE,
    SELECTED,
  };
  Q_ENUMS(VariantState);

  virtual int rowCount(const QModelIndex& parent) const override;
  virtual QVariant data(const QModelIndex& index, int role) const override;
  virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
  virtual QHash<int, QByteArray> roleNames() const override;

private:
  int _face;
  FaceCoords _faceCoords;
};

#endif // FACEVARIANTMODEL_H
