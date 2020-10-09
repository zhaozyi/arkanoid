#include "Paddle.h"

#include <ostream>

namespace arkanoid {

// TODO: Implement me
Paddle::Paddle(Point p, int32_t w, int32_t h, int32_t v) {
  /* Arguments:
    p: upper left corner of paddke (closest to (0,0))
    w: width of paddle
    h: height of paddle
    v: initial velocity of the paddle
  */
}

// TODO: Implement me
Point Paddle::getUpperLeft() const { return {}; }

// TODO: Implement me
Point Paddle::getLowerRight() const { return {}; }

// TODO: Implement me
int32_t Paddle::getVelocity() const { return 0; }

std::ostream &operator<<(std::ostream &os, const Paddle &paddle) {
  os << "Paddle { " << paddle.getUpperLeft() << ", " << paddle.getLowerRight()
     << ", velocity = " << paddle.getVelocity() << " }";
  return os;
}

} // namespace arkanoid
