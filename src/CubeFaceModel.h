#ifndef CUBEFACEMODEL_H
#define CUBEFACEMODEL_H

#include "IntVec3d.h"
#include <QtQml/qqmlregistration.h>
#include <QAbstractTableModel>
#include <array>
#include "FaceCoords.h"

class CubeModel;


class CubeFaceModel : public QAbstractTableModel
{
  Q_OBJECT
public:
  explicit CubeFaceModel(CubeModel* model, int face, QObject *parent = nullptr);

private:
  enum Roles{
    ColorRole = Qt::UserRole + 1,
    XRole,
    YRole,
    ZRole,
    ModelIndex,
  };
  int _face;
  CubeModel* _model;

  FaceCoords _faceCoords;

public:
  virtual int rowCount(const QModelIndex& parent) const override;
  virtual int columnCount(const QModelIndex& parent) const override;
  virtual QVariant data(const QModelIndex& index, int role) const override;
  virtual QHash<int, QByteArray> roleNames() const override;
  Q_INVOKABLE IntVec3d coordFromIndex(QVariant index) const;
};

#endif // CUBEFACEMODEL_H
