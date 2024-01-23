#ifndef FACECOORDS_H
#define FACECOORDS_H

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

public:
  std::array<int, 3> localToGlobalCoord(int x, int y) const;
  bool belongsToFace(int x, int y, int z) const;
  std::array<int, 2> getCoords(int x, int y, int z) const;


};

#endif // FACECOORDS_H
