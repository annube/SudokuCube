#include "EdgeVariantModel.h"

EdgeVariantModel::EdgeVariantModel(CubeModel* cubeModel, CubeModel::CubeColors color, QObject *parent)
  : VariantModel{cubeModel, 1, color, parent}, _faceCoords(0)

{
  _variantPieces.resize(numVariants());
  _variantPieces[0].push_back(_faceCoords.localToGlobalCoord(1,0,0));
  _variantPieces[0].push_back(_faceCoords.localToGlobalCoord(0,2,1));
  _variantPieces[0].push_back(_faceCoords.localToGlobalCoord(2,1,2));

  for(auto &variant: _variantPieces)
  {
    std::sort(variant.begin(), variant.end());
  }

}
