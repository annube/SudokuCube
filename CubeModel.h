#ifndef CUBEMODEL_H
#define CUBEMODEL_H


#include "IntVec3d.h"
#include "qobject.h"
#include "qtmetamacros.h"
#include <array>
#include <functional>
#include <boost/signals2/signal.hpp>
#include <QtQml/qqmlregistration.h>

class CubeFaceModel;

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


  Q_INVOKABLE void setValue(int x, int y, int z, CubeColors color);
  Q_INVOKABLE void setValue(QVariant coords, CubeColors color);
  Q_INVOKABLE CubeColors getValue(int x, int y, int z) const;

protected:
  int mapFromPhysicalCoordinates(int x, int y, int z) const;
  std::array<int, 3> mapToPhysicalCoordinates(int index) const;


private:
  std::array<CubeColors, 27> _sphereValues;
  boost::signals2::signal<void(int, int, int)> _preChange;
  boost::signals2::signal<void(int, int, int)> _postChange;
//  int physicalCoordinatesToLinearIndex[3][3][3];

};

#endif // CUBEMODEL_H
