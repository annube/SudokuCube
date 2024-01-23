#ifndef CUBEFACEMODEL_H
#define CUBEFACEMODEL_H

#include <array>

class CubeModel;


class FaceCoords
{
public:
  explicit FaceCoords(int face);

protected:
  int _face;
  std::array<int, 3> dim1Vec;
  std::array<int, 3> dim2Vec;

  std::array<int, 3> localToGlobalCoord(int x, int y) const;

};

#endif // CUBEFACEMODEL_H