#ifndef CORNERVARIANTMODEL_H
#define CORNERVARIANTMODEL_H

#include "VariantModel.h"
#include "FaceCoords.h"


class CornerVariantModel : public VariantModel
{
public:
  explicit CornerVariantModel(CubeModel* cubeModel, CubeModel::CubeColors color, QObject *parent = nullptr);
private:
  FaceCoords _faceCoords;

  // QAbstractItemModel interface
public:
  virtual QVariant data(const QModelIndex& index, int role) const override;
};

#endif // CORNERVARIANTMODEL_H
