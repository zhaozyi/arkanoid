#include "Ball.h"

#include <ostream>

namespace arkanoid {

// TODO: Implement me
Ball::Ball(Point c, int32_t r, Velocity v) : center{c.x, c.y}, velocity{v.vx, v.vy} {
  /* Arguments:
    c: center of ball
    r: radius of ball
    v: velocity of ball
  */
  radius = r;
}

// TODO: Implement me
Velocity Ball::getVelocity() const { return velocity; }

// TODO: Implement me
Point Ball::getCenter() const { return center; }

// TODO: Implement me
int32_t Ball::getRadius() const { return radius; }

// ------------ADDED FUNCTIONS-------------
/* update ball's location in the world */
void Ball::setLocation(Point p) {
  center = {p.x, p.y};
}
/* update ball's velocity to change direction in the world if collision occurs */
void Ball::setVelocity(Velocity v) {
  velocity = {v.vx, v.vy};
}
// ----------------------------------------

std::ostream &operator<<(std::ostream &os, const Ball &ball) {
  os << "Ball { center = " << ball.getCenter()
     << ", radius = " << ball.getRadius()
     << ", velocity = " << ball.getVelocity() << " }";
  return os;
}

} // namespace arkanoid
