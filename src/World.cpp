#include "World.h"

#include <ostream>

namespace arkanoid {

// TODO: Implement me
World::World(int32_t w, int32_t h, Ball b, Paddle p, std::vector<Brick> bs) {
  /* Arguments:
    w: width of the world
    h: height of the world
    b: a ball
    p: a paddle
    bs: a vector of bricks
  */
}

// TODO: Implement me
int32_t World::getWidth() const { return 0; }

// TODO: Implement me
int32_t World::getHeight() const { return 0; }

// TODO: Implement me
Ball World::getBall() const {}

// TODO: Implement me
Paddle World::getPaddle() const {}

// TODO: Implement me
std::vector<Brick> World::getBricks() const { return {}; }

// TODO: Implement me
bool World::isLegal() const {
  // Placeholder return--remove when finished
  return false;

  /* Users of this class are able to use the class’s constructor to
  create arbitrary game worlds, including worlds that contain an illegal
  game states. For example, there is nothing that prevents the user from
  constructing a world without any bricks, or a world with a ball of
  velocity zero. The `isLegal()` member function should detect such
  illegal initial game states. Specifically, it does the following checks: */

  /*
  There should be at least one brick in the world.
  */

  /*
  The ball must have a nonzero velocity.
  */

  /*
  All entities(ball, paddle, and bricks) must be *entirely* within the boundary
  of the world. This means that if one corner of a brick is within the world,
  but the other corner is not, it is out-of-bounds. Treat the ball as a square
  box for the purposes of this check.
  */

  /*
  Entities must not collide with one another.

  For collision detection, view all entities (including the ball) as a box,
  and use the simple Axis-Aligned Bounding Box algorithm. Note that according
  to the algorithm, if the bounding boxes of two game entities intersect only
  through an edge or through a vertex then this does not count as a collision.

  You may use an internet implementation of AABB, as long as you cite your
  source.

  More on AABB:
  https://developer.mozilla.org/en-US/docs/Games/Techniques/2D_collision_detection
  */
}

// TODO: Implement me
void World::update(Input in) {
  /* You may assume that the world is valid at the start of this function */

  /*
  This function takes the user input as a parameter, which is a scoped enum
  that has three possibilities:
     - Input::None (player does not press any key)
     - Input::Left (player wants to move the paddle to the left)
     - Input::Right(player wants to move the paddle to the right)

  Using this input, the game world should make the following updates: */

  /*
  First, the paddle moves (using its current velocity).
  If the original location of the paddle is (x, y), the new location would be
  (x + v, y), where v is the paddle’s velocity. However, if the paddle would
  move beyond the left (or right) boundary of the game world, you need to keep
  it inside the world and align it to the left (or right) world boundary. */

  /*
  Next, the paddle’s velocity changes according to the user input.
    - If the input is Input::None, set the velocity to zero.
    - If the input is Input::Left, set the velocity to -Paddle::DefaultVelocity.
    - If the input is Input::Right, set the velocity to Paddle::DefaultVelocity.
  */

  /*
  Now the ball moves. If the original location of the ball is (x, y), the
  new location would be (x + v_x, y + v_y), where v_x and v_y are the ball’s
  horizontal velocity and vertical velocity, respectively.

  After this step, it is OK if the ball moves to an illegal position
  (e.g. it goes outside of the game world, or it overlaps with either
  the paddle or some bricks). In the next step, we will fix that by
  changing the ball’s velocity in such a way that will move the ball
  out of the illegal position in the next couple of frames.
  */

  /*
  Now we resolve any collisions or illegal states that may have occurred from
  the previous step. Order of collision resolution is important!
  */

  /* If the ball collides with or goes beyond the left boundary of the world,
     set itshorizontal velocity to Ball::DefaultHorizontalVelocity. */

  /* If the ball collides with or goes beyond the right boundary of the world,
     set its horizontal velocity to -Ball::DefaultHorizontalVelocity.*/

  /* If the ball collides with or goes beyond the upper boundary of the world,
  set its vertical velocity toBall::DefaultVerticalVelocity */

  /* If the ball collides with the paddle, set its vertical velocity to
     -Ball::DefaultVerticalVelocity. */

  /* If the ball collides with or goes beyond the lower boundary of the world,
     the game is over. We handle this case by throwing an exception:
     throw GameOverException().

     Please do not actually do this for an actual game--we use exceptions here
     to keep things simple, but they are definitely not designed to be used like
     this. */

  /*
    Remove all bricks that collide with a ball. Instead of trying to hand-code
    this yourself, I suggest looking at std::remove_if in <algorithm> */
}

std::ostream &operator<<(std::ostream &os, const std::vector<Brick> &bricks) {
  os << "[ ";
  for (auto const &b : bricks)
    os << b << "; ";
  os << "]";
  return os;
}

std::ostream &operator<<(std::ostream &os, const World &world) {
  os << "World {\n  width = " << world.getWidth()
     << "\n  height = " << world.getHeight() << "\n  " << world.getBall()
     << ",\n  " << world.getPaddle() << ",\n  " << world.getBricks() << "\n}";

  return os;
}

} // namespace arkanoid
