#include "Paddle.h"

#include <ostream>

namespace arkanoid {

/* Class Members:
    paddleUpperLeftCorner: the upper left corner point of this paddle
    paddleVelocity: the velocity of paddle
    paddleWidth: the width of paddle
    paddleHeight: the height of paddle
*/
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


// get upper left point of this paddle
Point Paddle::getUpperLeft() const { return paddleUpperLeftCorner; }

// get lower right point of this paddle
Point Paddle::getLowerRight() const { return Point{paddleUpperLeftCorner.x + paddleWidth, paddleUpperLeftCorner.y + paddleHeight}; }

// get velocity of this paddle
int32_t Paddle::getVelocity() const { return paddleVelocity.vx; }

// get width of this paddle
int32_t Paddle::getPaddleWidth() const { return paddleWidth; }

// get height of this paddle
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
