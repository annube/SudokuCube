#include "FaceVariantModel.h"
#include "CubeModel.h"
#include <set>

FaceVariantModel::FaceVariantModel(CubeModel* cubeModel, int face, QObject *parent)
  : QAbstractListModel{parent}, _cubeModel(cubeModel), _face(face), _faceCoords(face)
  , _centerCoord(_faceCoords.localToGlobalCoord(1,1))

{

  _variantPieces.resize(numVariants());
  for(int variant = 0; variant < numVariants(); ++variant)
  {
    _variantPieces[variant].push_back(_faceCoords.localToGlobalCoord(1,1,0));
    _variantPieces[variant].push_back(_faceCoords.faceVariantEdgeCoord(variant));
    _variantPieces[variant].push_back(_faceCoords.faceVariantCornerCoord(variant));
    std::sort(_variantPieces[variant].begin(), _variantPieces[variant].end());
  }

  _cubeModel->registerPostChange([this](int x, int y, int z){
    dataChanged(index(0), index(numVariants()-1));
  });

}


int FaceVariantModel::rowCount(const QModelIndex& parent) const
{
  return numVariants();
}



QVariant FaceVariantModel::data(const QModelIndex& index, int role) const
{
  switch(role)
  {
  case Qt::DisplayRole:
    return QString("Variant %1").arg(index.row());
  case VariantPossible:
  {
    auto coordsWithCenterColor = _cubeModel->getCoordsWithValue(color());
    std::sort(coordsWithCenterColor.begin(), coordsWithCenterColor.end());

    if(coordsWithCenterColor.size()>_variantPieces.size() || !variantFree(index.row()))
    {
      return IMPOSSIBLE;
    }

    if(coordsWithCenterColor == _variantPieces[index.row()])
    {
      return SELECTED;
    }

    std::vector<std::array<int, 3>> commonPieces;
    std::set_intersection(coordsWithCenterColor.begin(), coordsWithCenterColor.end(), _variantPieces[index.row()].begin(), _variantPieces[index.row()].end(),
                          std::back_inserter(commonPieces));

    if(commonPieces == coordsWithCenterColor)
    {
      return POSSIBLE;
    }
    return IMPOSSIBLE;

  }
  case ModelIndex:
    return index;
  default:
    return QVariant();
  }
}

QVariant FaceVariantModel::headerData(int section, Qt::Orientation orientation, int role) const
{
  return QStringLiteral("Variant");
}

QHash<int, QByteArray> FaceVariantModel::roleNames() const
{
  return {
    {VariantPossible, "possible"},
    {ModelIndex, "modelIndex"},
  };
}

void FaceVariantModel::setVariant(int variant)
{
  if(variantFree(variant))
  {
    bool wasSelected = variantSelected(variant);
    // clear color
    _cubeModel->clearColor(color());

    if(!wasSelected) {
      // set new variant
      for(auto const& piece: _variantPieces[variant])
      {
        _cubeModel->setValue(piece, color());
      }
    }
  }
}

int FaceVariantModel::numVariants() const
{
  return 4;
}

CubeModel::CubeColors FaceVariantModel::color() const
{
  return CubeModel::faceCenterColor(_face);
}


bool FaceVariantModel::variantFree(int variant) const
{
  for(auto const& piece: _variantPieces[variant])
  {
    auto pieceValue = _cubeModel->getValue(piece);
    if( pieceValue != color() && pieceValue != CubeModel::FREE)
    {
      return false;
    }
  }
  return true;
}

bool FaceVariantModel::variantSelected(int variant) const
{
  for(auto const& piece: _variantPieces[variant])
  {
    auto pieceValue = _cubeModel->getValue(piece);
    if( pieceValue != color())
    {
      return false;
    }
  }
  return true;
}
