#ifndef CUBEFACEMODEL_H
#define CUBEFACEMODEL_H

#include <QtQml/qqmlregistration.h>
#include <QAbstractTableModel>
#include <array>

class CubeModel;

class IntVec3d: public std::array<int, 3>
{
  Q_GADGET
  QML_VALUE_TYPE(intvec3d)
public:
  using Base=std::array<int, 3>;
  using Base::Base;
  IntVec3d(Base const& other): Base(other){}
};

class CubeFaceModel : public QAbstractTableModel
{
  Q_OBJECT
public:
  explicit CubeFaceModel(CubeModel* model, int face, QObject *parent = nullptr);

private:
  enum Roles{
    ColorRole = Qt::UserRole + 1,
    XRole,
    YRole,
    ZRole,
  };
  int _face;
  CubeModel* _model;
  std::array<int, 3> dim1Vec;
  std::array<int, 3> dim2Vec;

  // QAbstractItemModel interface
public:
  virtual int rowCount(const QModelIndex& parent) const override;
  virtual int columnCount(const QModelIndex& parent) const override;
  virtual QVariant data(const QModelIndex& index, int role) const override;
  virtual QHash<int, QByteArray> roleNames() const override;
  IntVec3d coordFromIndex(QModelIndex const& index) const;
};

#endif // CUBEFACEMODEL_H
