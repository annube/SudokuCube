#include "FaceVariantModel.h"
#include "CubeModel.h"
#include <set>

FaceVariantModel::FaceVariantModel(CubeModel* cubeModel, int face, QObject *parent)
  : VariantModel{cubeModel, 4, CubeModel::faceCenterColor(face), parent}, _face(face), _faceCoords(face)

{

  _variantPieces.resize(numVariants());
  for(int variant = 0; variant < numVariants(); ++variant)
  {
    _variantPieces[variant].push_back(_faceCoords.localToGlobalCoord(1,1,0));
    _variantPieces[variant].push_back(_faceCoords.faceVariantEdgeCoord(variant));
    _variantPieces[variant].push_back(_faceCoords.faceVariantCornerCoord(variant));
    std::sort(_variantPieces[variant].begin(), _variantPieces[variant].end());
  }

}

