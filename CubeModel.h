#ifndef CUBEMODEL_H
#define CUBEMODEL_H


#include "qobject.h"
#include "qtmetamacros.h"
#include <array>
#include <functional>
#include <boost/signals2/signal.hpp>
#include <QtQml/qqmlregistration.h>

class CubeFaceModel;
class FaceVariantModel;
class EdgeVariantModel;

class CubeModel: public QObject
{
  Q_OBJECT
  QML_ELEMENT
public:

  enum CubeColors {
    CONFLICT=-1,
    BLACK,
    WHITE,
    YELLOW,
    ORANGE,
    LIGHT_BLUE,
    BLUE,
    PURPLE,
    RED,
    GREEN,
    FREE,
    NUM_COLORS = FREE,
  };

  Q_ENUM(CubeColors)
  Q_ENUMS(CubeColors);

  CubeModel();

  boost::signals2::connection registerPreChange(std::function<void(int, int, int)>&& pred);
  boost::signals2::connection registerPostChange(std::function<void(int, int, int)>&& pred);

  Q_INVOKABLE CubeFaceModel* getFace(int face);
  Q_INVOKABLE QVariant getFaceVariant(int face);
  Q_INVOKABLE QVariant getEdgeVariant(CubeColors color);
  Q_INVOKABLE QVariant getCornerVariant(CubeColors color);


  Q_INVOKABLE void setValue(QVariant coords, CubeColors color);
  Q_INVOKABLE CubeColors getValue(int x, int y, int z) const;
  void setValue(std::array<int, 3> coord, CubeColors color);
  void setValue(int x, int y, int z, CubeColors color);
  CubeColors getValue(std::array<int, 3> vec) const;
  std::vector<std::array<int, 3>> getCoordsWithValue(CubeColors value) const;
  static CubeColors faceCenterColor(int face);
  void clearColor(CubeColors value);

protected:
  int mapFromPhysicalCoordinates(int x, int y, int z) const;
  std::array<int, 3> mapToPhysicalCoordinates(int index) const;
  static bool isCenter(std::array<int, 3> const& point);


private:
  std::array<CubeColors, 27> _sphereValues;
  boost::signals2::signal<void(int, int, int)> _preChange;
  boost::signals2::signal<void(int, int, int)> _postChange;
//  int physicalCoordinatesToLinearIndex[3][3][3];

};

#endif // CUBEMODEL_H
