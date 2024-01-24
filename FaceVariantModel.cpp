#include "FaceVariantModel.h"

FaceVariantModel::FaceVariantModel(int face, QObject *parent)
  : QAbstractListModel{parent}, _face(face), _faceCoords(face)
{

}

int FaceVariantModel::rowCount(const QModelIndex& parent) const
{
}

QVariant FaceVariantModel::data(const QModelIndex& index, int role) const
{
}

QVariant FaceVariantModel::headerData(int section, Qt::Orientation orientation, int role) const
{
}

QHash<int, QByteArray> FaceVariantModel::roleNames() const
{
}
