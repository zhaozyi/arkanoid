#include "Paddle.h"

#include <ostream>

namespace arkanoid {

// TODO: Implement me
Paddle::Paddle(Point p, int32_t w, int32_t h, int32_t v) : paddleUpperLeftCorner{p.x, p.y}, paddleVelocity{v, 0} {
  /* Arguments:
    p: upper left corner of paddke (closest to (0,0))
    w: width of paddle
    h: height of paddle
    v: initial velocity of the paddle
  */
  paddleWidth = w;
  paddleHeight = h;
}


// TODO: Implement me
Point Paddle::getUpperLeft() const { return paddleUpperLeftCorner; }

// TODO: Implement me
Point Paddle::getLowerRight() const { return Point{paddleUpperLeftCorner.x + paddleWidth, paddleUpperLeftCorner.y + paddleHeight}; }

// TODO: Implement me
int32_t Paddle::getVelocity() const { return paddleVelocity.vx; }

int32_t Paddle::getPaddleWidth() const { return paddleWidth; }

int32_t Paddle::getPaddleHeight() const { return paddleHeight; }

// ---------ADDED FUNCTIONS------------
/* update paddle's location in the world */
void Paddle::setLocation(Point p) {
  paddleUpperLeftCorner = {p.x, p.y};
}

/* change paddle's velocity */
void Paddle::setVelocity(Velocity v) {
  paddleVelocity = {v.vx, v.vy};
}
// -----------------------------------

std::ostream &operator<<(std::ostream &os, const Paddle &paddle) {
  os << "Paddle { " << paddle.getUpperLeft() << ", " << paddle.getLowerRight()
     << ", velocity = " << paddle.getVelocity() << " }";
  return os;
}

} // namespace arkanoid
