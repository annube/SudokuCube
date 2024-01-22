#include "ColorModel.h"
#include "CubeModel.h"
#include "qmetaobject.h"


namespace
{

template<typename QEnum>
std::string QtEnumToString (const QEnum value)
{
  return QMetaEnum::fromType<QEnum>().valueToKey(value);
}

}
ColorModel::ColorModel(QObject *parent)
  : QAbstractListModel(parent)
{
}

QVariant ColorModel::headerData(int section, Qt::Orientation orientation, int role) const
{
  return QStringLiteral("color");
}

int ColorModel::rowCount(const QModelIndex &parent) const
{
  return CubeModel::NUM_COLORS;
}

QVariant ColorModel::data(const QModelIndex &index, int role) const
{
  if (!index.isValid())
    return QVariant();

  switch(role)
  {
  case Qt::DisplayRole:
    return QString::fromStdString(QtEnumToString(static_cast<CubeModel::CubeColors>(index.row())));
  case ColorRole:
    return QVariant::fromValue(static_cast<CubeModel::CubeColors>(index.row()));
  default:
    return QVariant();
  }
}


QHash<int, QByteArray> ColorModel::roleNames() const
{
  return {{Qt::DisplayRole, "display"},
    { ColorRole, "color"},
  };
}
