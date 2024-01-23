#include "CubeModel.h"
#include "CubeFaceModel.h"

CubeModel::CubeModel()
{
  std::fill(_sphereValues.begin(), _sphereValues.end(), FREE);
  setValue(1,1,0, BLACK);
  setValue(1,1,2, WHITE);
  setValue(1,0,1,YELLOW);
  setValue(1,2,1,ORANGE);
  setValue(0,1,1,LIGHT_BLUE);
  setValue(2,1,1,BLUE);
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

void CubeModel::setValue(int x, int y, int z, CubeColors color)
{
  _preChange(x,y,z);
  _sphereValues[mapFromPhysicalCoordinates(x,y,z)]=color;
  _postChange(x,y,z);
}

void CubeModel::setValue(QVariant coords, CubeColors color)
{
  auto rCoords = coords.value<IntVec3d>();
  setValue(rCoords[0], rCoords[1], rCoords[2], color);
}

CubeModel::CubeColors CubeModel::getValue(int x, int y, int z) const
{
  return _sphereValues[mapFromPhysicalCoordinates(x,y,z)];
}

