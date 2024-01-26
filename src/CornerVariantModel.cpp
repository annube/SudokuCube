#include "CornerVariantModel.h"

CornerVariantModel::CornerVariantModel(CubeModel* cubeModel, CubeModel::CubeColors color, QObject *parent)
  : VariantModel{cubeModel, 4, color, parent}, _faceCoords(0)

{
  _variantPieces.resize(numVariants());

  std::array<int, 3> variantPositions[2] = {
    {0,0,0},
    {2,2,2},
  };

  auto applyVariant = [&, index=0] (std::array<int, 3> const* variantPositions) mutable {

    for(int i=0; i < 2; ++i){
      _variantPieces[index].push_back(_faceCoords.localToGlobalCoord(variantPositions[i][0],variantPositions[i][1], variantPositions[i][2]));
    }
    ++index;
  };

  auto rotatePositions= [this](std::array<int, 3>* variantPositions)
  {
    for(int i = 0 ; i < 2; ++i)
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


QVariant CornerVariantModel::data(const QModelIndex& index, int role) const
{
  return VariantModel::data(index, role);
}
