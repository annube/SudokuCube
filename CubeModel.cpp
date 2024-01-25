#include "FaceVariantModel.h"
#include "CubeModel.h"
#include "CubeFaceModel.h"
#include "EdgeVariantModel.h"

CubeModel::CubeModel()
{
  std::fill(_sphereValues.begin(), _sphereValues.end(), FREE);
//  setValue(1,1,0, BLACK);
//  setValue(1,1,2, WHITE);
//  setValue(1,0,1,YELLOW);
//  setValue(1,2,1,ORANGE);
//  setValue(0,1,1,LIGHT_BLUE);
//  setValue(2,1,1,BLUE);
}

boost::signals2::connection CubeModel::registerPreChange(std::function<void (int, int, int)>&& pred)
{
  return _preChange.connect(pred);
}

boost::signals2::connection CubeModel::registerPostChange(std::function<void (int, int, int)>&& pred)
{
  return _postChange.connect(pred);
}

CubeFaceModel* CubeModel::getFace(int face)
{
  auto result = new CubeFaceModel(this, face, this);
  return result;
}

QVariant CubeModel::getFaceVariant(int face)
{
  auto result = new FaceVariantModel(this, face, this);
  return QVariant::fromValue<FaceVariantModel*>(result);
}

QVariant CubeModel::getEdgeVariant(CubeColors color)
{
  auto result = new EdgeVariantModel(this, RED, this);
  return QVariant::fromValue<EdgeVariantModel*>(result);
}


int CubeModel::mapFromPhysicalCoordinates(int x, int y, int z) const
{
  return x + 3*(y + 3*z);
}

std::array<int, 3> CubeModel::mapToPhysicalCoordinates(int index) const
{
  int x = index % 3;
  int y = (index / 3) % 3;
  int z = (index / 9);
  return {x, y, z};
}

bool CubeModel::isCenter(const std::array<int, 3>& point)
{
  static std::array<int, 3> v[]={
    {1,1,0},
    {1,1,2},
    {1,0,1},
    {1,2,1},
    {0,1,1},
    {2,1,1},
  };
  for(auto p : v){
    if(point[0] == p[0] && point[1] == p[1] && point[2] == p[2])
    {
      return true;
    }
  }
  return false;
}

void CubeModel::setValue(int x, int y, int z, CubeColors color)
{
  _preChange(x,y,z);
  _sphereValues[mapFromPhysicalCoordinates(x,y,z)]=color;
  _postChange(x,y,z);
}

void CubeModel::setValue(QVariant coords, CubeColors color)
{
  auto rCoords = coords.value<IntVec3d>();
  if(!isCenter(rCoords)){
    setValue(rCoords[0], rCoords[1], rCoords[2], color);
  }
}

CubeModel::CubeColors CubeModel::getValue(int x, int y, int z) const
{
  return _sphereValues[mapFromPhysicalCoordinates(x,y,z)];
}

void CubeModel::setValue(std::array<int, 3> coord, CubeColors color)
{
  setValue(coord[0], coord[1], coord[2], color);
}

CubeModel::CubeColors CubeModel::getValue(std::array<int, 3> vec) const
{
  return getValue(vec[0], vec[1], vec[2]);
}

std::vector<std::array<int, 3> > CubeModel::getCoordsWithValue(CubeColors value) const
{
  std::vector<std::array<int, 3> > result;
  for(int i = 0 ; i < _sphereValues.size(); ++i)
  {
    if(_sphereValues[i] == value)
    {
      result.push_back(mapToPhysicalCoordinates(i));
    }
  }
  return result;
}

CubeModel::CubeColors CubeModel::faceCenterColor(int face)
{
  switch(face){
  case 0:
    return BLACK;
  case 1:
    return ORANGE;
  case 2:
    return YELLOW;
  case 3:
    return WHITE;
  case 4:
    return BLUE;
  case 5:
    return LIGHT_BLUE;
  }
  throw(std::logic_error("Face must be in range 0-5"));
}

void CubeModel::clearColor(CubeColors value)
{
  for(int i = 0 ; i < _sphereValues.size(); ++i)
  {
    auto coords = mapToPhysicalCoordinates(i);
    if(_sphereValues[i] == value && !isCenter(coords))
    {
      setValue(coords, FREE);
    }
  }
}

