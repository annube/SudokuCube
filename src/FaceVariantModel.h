#ifndef FACEVARIANTMODEL_H
#define FACEVARIANTMODEL_H

#include <FaceCoords.h>
#include <QtQml/qqmlregistration.h>
#include "VariantModel.h"

class CubeModel;
class FaceVariantModel : public VariantModel
{
  Q_OBJECT
  QML_ELEMENT
public:
  explicit FaceVariantModel(CubeModel* cubeModel, int face, QObject *parent = nullptr);

  // QAbstractItemModel interface
public:

private:
  int _face;
  FaceCoords _faceCoords;

};

#endif // FACEVARIANTMODEL_H
