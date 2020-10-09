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

private:
};

// Additional logic to let std::cout work with Paddle objects
std::ostream &operator<<(std::ostream &, const Paddle &); // SKELETON

} // namespace arkanoid
