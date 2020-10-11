#include "Brick.h"

#include <ostream>

namespace arkanoid {

/* class members:
  upperLeftCorner: the upper left corner vertex of this brick
  width: width of brick
  height: height of brick
*/
Brick::Brick(Point p, int32_t w, int32_t h) : upperLeftCorner{p.x, p.y} {
  /* Arguments:
    p: upper left corner of brick (closest to (0,0))
    w: width of brick
    h: height of brick
  */
  width = w;
  height = h;
}

// get the upperLeftCorner point's coordinate of this brick
Point Brick::getUpperLeft() const { return upperLeftCorner; }

// get the lowerRight point's coordinate of this brick
Point Brick::getLowerRight() const { return Point{upperLeftCorner.x + width, upperLeftCorner.y + height}; }

// get the width of this brick
int32_t Brick::getBrickWidth() const { return width; }

// get the height of this brick
int32_t Brick::getBrickHeight() const { return height; }



std::ostream &operator<<(std::ostream &os, const Brick &brick) {
  os << "Brick { " << brick.getUpperLeft() << ", " << brick.getLowerRight()
     << " }";
  return os;
}

} // namespace arkanoid
