#pragma once

#include "Input.h"
#include "Point.h"

#include <iosfwd>
#include <utility>

namespace arkanoid {

class Paddle {
public:
  static constexpr int32_t DefaultVelocity = 4; // SKELETON

  // Implement the member functions listed below

  Paddle(Point p, int32_t w, int32_t h, int32_t v); // SKELETON

  Point getUpperLeft() const;  // SKELETON
  Point getLowerRight() const; // SKELETON
  int32_t getVelocity() const; // SKELETON
  // ADDED FUNCTIONS
  int32_t getPaddleWidth() const;
  int32_t getPaddleHeight() const;
  void setLocation(Point p);
  void setVelocity(Velocity v);

private:
  Point paddleUpperLeftCorner;
  int32_t paddleWidth;
  int32_t paddleHeight;
  Velocity paddleVelocity;
};

// Additional logic to let std::cout work with Paddle objects
std::ostream &operator<<(std::ostream &, const Paddle &); // SKELETON

} // namespace arkanoid
