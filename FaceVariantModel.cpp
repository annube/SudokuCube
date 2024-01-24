#include "FaceVariantModel.h"

FaceVariantModel::FaceVariantModel(int face, QObject *parent)
  : QAbstractListModel{parent}, _face(face), _faceCoords(face)
{

}

int FaceVariantModel::rowCount(const QModelIndex& parent) const
{
  return 4;
}

QVariant FaceVariantModel::data(const QModelIndex& index, int role) const
{
  switch(role)
  {
  case Qt::DisplayRole:
    return QString("Variant %1").arg(index.row());
  case VariantPossible:
    return POSSIBLE;
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
