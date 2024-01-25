#ifndef VARIANTMODEL_H
#define VARIANTMODEL_H

#include <QAbstractListModel>
#include <QtQml/qqmlregistration.h>
#include "CubeModel.h"

class CubeModel;
class VariantModel : public QAbstractListModel
{
  Q_OBJECT
  QML_ELEMENT
public:
  explicit VariantModel(CubeModel* cubeModel, int numVariants, CubeModel::CubeColors color, QObject *parent = nullptr);

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
  Q_INVOKABLE void setVariant(int variant);

  int numVariants() const;
  CubeModel::CubeColors color() const;

protected:
  std::vector<std::vector<std::array<int, 3>>> _variantPieces;

private:
  bool variantFree(int variant) const;
  bool variantSelected(int variant) const;
  CubeModel* _cubeModel;
  int _numVariants;
  CubeModel::CubeColors _color;


};

#endif // FACEVARIANTMODEL_H
