#ifndef INTVEC3D_H
#define INTVEC3D_H

#include <QObject>
#include <QtQml/qqmlregistration.h>
#include <array>


class IntVec3d: public std::array<int, 3>
{
  Q_GADGET
  QML_VALUE_TYPE(intvec3d)
public:
  using Base=std::array<int, 3>;
  using Base::Base;
  IntVec3d(Base const& other): Base(other){}
  int x() const;
  int y() const;
  int z() const;
};

#endif // INTVEC3D_H
