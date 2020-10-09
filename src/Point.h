#pragma once

#include <cstdint>
#include <iosfwd>

namespace arkanoid {

/* This class represents a point on the screen. Note that it is an aggregate
class, so it can be constructed in-place like so:

Point p{3,4}
OR
Point p = {3,4};

The C++ compiler will generate this constructor for you as long as you don't
define any of your own constructors (which you should not).
*/

// SKELETON: Do not edit this class definition!
struct Point {
  int32_t x, y;

  // Don't construct default points!
  Point() = delete;
};

/* Represents velocity of some object. Each frame, the position of an object
should change by some multiple of its velocity */
struct Velocity {
  int32_t vx, vy;
};

std::ostream &operator<<(std::ostream &, Point);
std::ostream &operator<<(std::ostream &, Velocity);

} // namespace arkanoid
