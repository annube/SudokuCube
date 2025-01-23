#include "VariantModel.h"
#include "CubeModel.h"
#include <iostream>
#include <set>

VariantModel::VariantModel(CubeModel* cubeModel, int numVariants, CubeModel::CubeColors color, QObject *parent)
  : QAbstractListModel{parent}, _cubeModel(cubeModel), _numVariants(numVariants), _color(color)
{

  _cubeModel->registerPostChange([this](int x, int y, int z){
    dataChanged(index(0), index(this->numVariants()-1));
  });

}


int VariantModel::rowCount(const QModelIndex& parent) const
{
  return numVariants();
}



QVariant VariantModel::data(const QModelIndex& index, int role) const
{
  switch(role)
  {
  case Qt::DisplayRole:
    return QString("Variant %1").arg(index.row());
  case VariantPossible:
  {
    auto coordsWithCenterColor = _cubeModel->getCoordsWithValue(color());
    std::sort(coordsWithCenterColor.begin(), coordsWithCenterColor.end());

    if(coordsWithCenterColor == _variantPieces[index.row()])
    {
      return SELECTED;
    }
    if(variantFree(index.row()))
    {
      return POSSIBLE;
    } else {
      return IMPOSSIBLE;
    }

  }
  case ModelIndex:
    return index;
  default:
    return QVariant();
  }
}

QVariant VariantModel::headerData(int section, Qt::Orientation orientation, int role) const
{
  return QStringLiteral("Variant");
}

QHash<int, QByteArray> VariantModel::roleNames() const
{
  return {
    {VariantPossible, "possible"},
    {ModelIndex, "modelIndex"},
  };
}

void VariantModel::setVariant(int variant)
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

int VariantModel::numVariants() const
{
  return _numVariants;
}

CubeModel::CubeColors VariantModel::color() const
{
  return _color;
}


bool VariantModel::variantFree(int variant) const
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

bool VariantModel::variantSelected(int variant) const
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
