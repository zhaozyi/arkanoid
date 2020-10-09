#pragma once

#include "Paddle.h"

#include <iosfwd>
#include <utility>

namespace arkanoid {

class Ball {
public:
  static constexpr int32_t DefaultHorizontalVelocity = 1; // SKELETON
  static constexpr int32_t DefaultVerticalVelocity = 1;   // SKELETON

  // Implement the member functions listed below
  Ball(Point c, int32_t r, Velocity v); // SKELETON

  Velocity getVelocity() const; // SKELETON
  Point getCenter() const;      // SKELETON
  int32_t getRadius() const;    // SKELETON

private:
  // Add any instance variables you need here
};

// Additional logic to let std::cout work with Ball objects
std::ostream &operator<<(std::ostream &, const Ball &); // SKELETON

} // namespace arkanoid
