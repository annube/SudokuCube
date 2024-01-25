#include "EdgeVariantModel.h"

EdgeVariantModel::EdgeVariantModel(CubeModel* cubeModel, CubeModel::CubeColors color, QObject *parent)
  : VariantModel{cubeModel, 8, color, parent}, _faceCoords(0)

{
  _variantPieces.resize(numVariants());

  std::array<int, 3> variantPositions[6] = {
    {1,0,0},
    {0,2,1},
    {2,1,2},
    {1,0,0},
    {2,2,1},
    {0,1,2},
  };

  auto applyVariant = [&, index=0] (std::array<int, 3> const* variantPositions) mutable {

    for(int i=0; i < 3; ++i){
      _variantPieces[index].push_back(_faceCoords.localToGlobalCoord(variantPositions[i][0],variantPositions[i][1], variantPositions[i][2]));
    }
    ++index;
    for(int i=3; i < 6; ++i){
      _variantPieces[index].push_back(_faceCoords.localToGlobalCoord(variantPositions[i][0],variantPositions[i][1], variantPositions[i][2]));
    }
    ++index;
  };

  auto rotatePositions= [this](std::array<int, 3>* variantPositions)
  {
    for(int i = 0 ; i < 6; ++i)
    {
      auto& v=variantPositions[i];
      auto x=2-v[1];
      v[1]=v[0];
      v[0]=x;

    }
  };

  applyVariant(variantPositions);
  rotatePositions(variantPositions);
  applyVariant(variantPositions);
  rotatePositions(variantPositions);
  applyVariant(variantPositions);
  rotatePositions(variantPositions);
  applyVariant(variantPositions);

  for(auto &variant: _variantPieces)
  {
    std::sort(variant.begin(), variant.end());
  }

}


QVariant EdgeVariantModel::data(const QModelIndex& index, int role) const
{
  return VariantModel::data(index, role);
}
