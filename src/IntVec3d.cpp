#include "IntVec3d.h"

int IntVec3d::x() const
{
  return (*this)[0];
}

int IntVec3d::y() const
{
  return (*this)[1];
}

int IntVec3d::z() const
{
  return (*this)[2];
}
