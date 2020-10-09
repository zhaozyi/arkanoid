#include "Brick.h"

#include <ostream>

namespace arkanoid {

// TODO: Implement me
Brick::Brick(Point p, int32_t w, int32_t h) {
  /* Arguments:
    p: upper left corner of brick (closest to (0,0))
    w: width of brick
    h: height of brick
  */
}

// TODO: Implement me
Point Brick::getUpperLeft() const { return {}; }

// TODO: Implement me
Point Brick::getLowerRight() const { return {}; }

std::ostream &operator<<(std::ostream &os, const Brick &brick) {
  os << "Brick { " << brick.getUpperLeft() << ", " << brick.getLowerRight()
     << " }";
  return os;
}

} // namespace arkanoid
