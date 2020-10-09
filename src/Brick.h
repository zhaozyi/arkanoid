#pragma once

#include "Point.h"

#include <iosfwd>

namespace arkanoid {

/*
Brick represents a brick that the player has to destroy. Like the Paddle class,
it has a rectangle shape. However, it does not have a velocity, because
bricks can't move.
*/

class Brick {
public:
  // Implement the member functions listed below
  Brick() = default;                    // SKELETON
  Brick(Point p, int32_t w, int32_t h); // SKELETON

  Point getUpperLeft() const;  // SKELETON
  Point getLowerRight() const; // SKELETON

private:
  // Add any instance variables you need here
};

// Additional logic to let std::cout work with Brick objects
std::ostream &operator<<(std::ostream &, const Brick &); // SKELETON

} // namespace arkanoid
