#include "Ball.h"

#include <ostream>

namespace arkanoid {

// TODO: Implement me
Ball::Ball(Point c, int32_t r, Velocity v) {
  /* Arguments:
    c: center of ball
    r: radius of ball
    v: velocity of ball
  */
}

// TODO: Implement me
Velocity Ball::getVelocity() const { return {}; }

// TODO: Implement me
Point Ball::getCenter() const { return {}; }

// TODO: Implement me
int32_t Ball::getRadius() const { return 0; }

std::ostream &operator<<(std::ostream &os, const Ball &ball) {
  os << "Ball { center = " << ball.getCenter()
     << ", radius = " << ball.getRadius()
     << ", velocity = " << ball.getVelocity() << " }";
  return os;
}

} // namespace arkanoid
