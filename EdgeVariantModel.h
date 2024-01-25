#ifndef EDGEVARIANTMODEL_H
#define EDGEVARIANTMODEL_H

#include "VariantModel.h"
#include "FaceCoords.h"


class EdgeVariantModel : public VariantModel
{
public:
  explicit EdgeVariantModel(CubeModel* cubeModel, CubeModel::CubeColors color, QObject *parent = nullptr);
private:
  FaceCoords _faceCoords;

  // QAbstractItemModel interface
public:
  virtual QVariant data(const QModelIndex& index, int role) const override;
};

#endif // EDGEVARIANTMODEL_H
