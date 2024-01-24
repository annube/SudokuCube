#include "FaceCoords.h"
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
  {{1,0,0},{0,1,0}},
  {{1,0,0},{0,0,1}},
  {{1,0,0},{0,0,-1}},
  {{1,0,0},{0,-1,0}},
  {{0,0,1},{0,1,0}},
  {{0,0,-1},{0,1,0}},
};


static int faceVecsOrigin[][3] = {
  {0,0,0},
  {0,2,0},
  {0,0,2},
  {0,2,2},
  {2,0,0},
  {0,0,2},
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



FaceCoords::FaceCoords(int face)
  : _face(face)
{

  std::copy(faceVecs[_face][0], faceVecs[_face][0]+3, dim1Vec.data());
  std::copy(faceVecs[_face][1], faceVecs[_face][1]+3, dim2Vec.data());

}

std::array<int, 3> FaceCoords::localToGlobalCoord(int x, int y) const
{
  auto destPoint{dim1Vec};
  boost::geometry::multiply_value(destPoint, x);
  {
    auto destPointAdd{dim2Vec};
    boost::geometry::multiply_value(destPointAdd, y);
    boost::geometry::add_point(destPoint, destPointAdd);
  }
  boost::geometry::add_point(destPoint, faceVecsOrigin[_face]);
  return {destPoint};
}

bool FaceCoords::belongsToFace(int x, int y, int z) const
{
  return ::belongsToFace(_face, x, y, z);
}

std::array<int, 2> FaceCoords::getCoords(int x, int y, int z) const
{
  return ::getCoords(_face, x, y, z);
}

std::array<int, 3> FaceCoords::faceVariantEdgeCoord(int variant) const
{

}

