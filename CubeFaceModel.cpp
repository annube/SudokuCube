#include "CubeFaceModel.h"
#include "CubeModel.h"
#include <boost/geometry.hpp>
#include <boost/geometry/geometries/adapted/std_array.hpp>
#include <boost/geometry/geometries/adapted/c_array.hpp>

BOOST_GEOMETRY_REGISTER_STD_ARRAY_CS(cs::cartesian)
BOOST_GEOMETRY_REGISTER_C_ARRAY_CS(cs::cartesian)

//
//    *-*
//    |1|
//  *-*-*-*
//  |5|0|4|
//  *-*-*-*
//    |2|
//    *-*
//    |3|
//    *-*
//
//
//
//
//
//



static int faceVecs[][2][3] = {
  {{1,0,0},{0,-1,0}},
  {{1,0,0},{0,0,-1}},
  {{1,0,0},{0,0,1}},
  {{1,0,0},{0,1,0}},
  {{0,0,1},{0,-1,0}},
  {{0,0,-1},{0,-1,0}},
};


static int faceVecsOrigin[][3] = {
  {0,2,0},
  {0,2,2},
  {0,0,0},
  {0,0,2},
  {2,2,0},
  {0,2,2},
};

namespace {
bool belongsToFace(int face, int x, int y, int z)
{
  switch(face)
  {
  case 0:
    return z==0;
    break;
  case 1:
    return y==2;
    break;
  case 2:
    return y==0;
    break;
  case 3:
    return z==2;
    break;
  case 4:
    return x==2;
    break;
  case 5:
    return x==0;
    break;
  }
  throw std::logic_error("Should never happen");
};

std::array<int, 2> getCoords(int face, int x, int y, int z)
{
  std::array<int, 2> result = {0, 0};
  std::array<int, 3> inputVec = {x, y, z};
  for(int coordIndex = 0; coordIndex <2; ++coordIndex)
  {
    for(int dimIndex = 0; dimIndex < 3; ++dimIndex)
    {
      result[coordIndex] += (inputVec[dimIndex]-faceVecsOrigin[face][dimIndex]) * faceVecs[face][coordIndex][dimIndex];
    }

  }
  return result;
}
}



CubeFaceModel::CubeFaceModel(CubeModel* model, int face, QObject *parent)
  : QAbstractTableModel{parent}, _face(face), _model(model)
{

  std::copy(faceVecs[_face][0], faceVecs[_face][0]+3, dim1Vec.data());
  std::copy(faceVecs[_face][1], faceVecs[_face][1]+3, dim2Vec.data());

  model->registerPostChange([this](int x, int y, int z){
    if(belongsToFace(_face, x, y, z)){
      auto coords = getCoords(_face, x, y, z);
      auto changedIndex = index(coords[1], coords[0]);
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
  };
}

IntVec3d CubeFaceModel::coordFromIndex(const QModelIndex& index) const
{
  auto destPoint{dim1Vec};
  boost::geometry::multiply_value(destPoint, index.column());
  {
    auto destPointAdd{dim2Vec};
    boost::geometry::multiply_value(destPointAdd, index.row());
    boost::geometry::add_point(destPoint, destPointAdd);
  }
  boost::geometry::add_point(destPoint, faceVecsOrigin[_face]);
  return {destPoint};
}

