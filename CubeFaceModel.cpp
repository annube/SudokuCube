#include "CubeFaceModel.h"
#include "CubeModel.h"
#include <boost/geometry.hpp>
#include <boost/geometry/geometries/adapted/std_array.hpp>
#include <boost/geometry/geometries/adapted/c_array.hpp>

BOOST_GEOMETRY_REGISTER_STD_ARRAY_CS(cs::cartesian)
BOOST_GEOMETRY_REGISTER_C_ARRAY_CS(cs::cartesian)




CubeFaceModel::CubeFaceModel(CubeModel* model, int face, QObject *parent)
  : QAbstractTableModel{parent}, _face(face), _model(model), _faceCoords(_face)
{


  model->registerPostChange([this](int x, int y, int z){
    if(_faceCoords.belongsToFace(x, y, z)){
      auto coords = _faceCoords.getCoords(x, y, z);
      auto changedIndex = index(2-coords[1], coords[0]);
      dataChanged(changedIndex, changedIndex);
    }
  });
}


int CubeFaceModel::rowCount(const QModelIndex& parent) const
{
  return 3;
}

int CubeFaceModel::columnCount(const QModelIndex& parent) const
{
  return 3;
}



QVariant CubeFaceModel::data(const QModelIndex& index, int role) const
{
  switch (role) {
  case Qt::DisplayRole:
    return QString("%1, %2").arg(index.column()).arg(index.row());
  case ColorRole:
  {
    auto destPoint = coordFromIndex(index);
    return QVariant::fromValue(_model->getValue(destPoint[0], destPoint[1], destPoint[2]));
  }
  case ModelIndex:
    return QVariant::fromValue(index);
  default:
    break;
  }

  return QVariant();
}


QHash<int, QByteArray> CubeFaceModel::roleNames() const
{
  return {
    {ColorRole, "color"},
    {XRole, "x"},
    {YRole, "y"},
    {ZRole, "z"},
    {ModelIndex, "modelIndex"},
  };
}

IntVec3d CubeFaceModel::coordFromIndex(QVariant index) const
{
  auto modelIndex = index.value<QModelIndex>();
  return {_faceCoords.localToGlobalCoord(modelIndex.column(), 2-modelIndex.row())};
}


