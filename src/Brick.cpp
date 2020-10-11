#include "Brick.h"

#include <ostream>

namespace arkanoid {

// TODO: Implement me
Brick::Brick(Point p, int32_t w, int32_t h) : upperLeftCorner{p.x, p.y} {
  /* Arguments:
    p: upper left corner of brick (closest to (0,0))
    w: width of brick
    h: height of brick
  */
  width = w;
  height = h;
}

// TODO: Implement me
Point Brick::getUpperLeft() const { return upperLeftCorner; }

// TODO: Implement me
Point Brick::getLowerRight() const { return Point{upperLeftCorner.x + width, upperLeftCorner.y + height}; }

// --------------ADDED FUNCTIONS-------------------
int32_t Brick::getBrickWidth() const { return width; }

int32_t Brick::getBrickHeight() const { return height; }



std::ostream &operator<<(std::ostream &os, const Brick &brick) {
  os << "Brick { " << brick.getUpperLeft() << ", " << brick.getLowerRight()
     << " }";
  return os;
}

} // namespace arkanoid
