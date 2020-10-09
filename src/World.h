#pragma once

#include "Ball.h"
#include "Brick.h"
#include "Input.h"
#include "Paddle.h"

#include <iosfwd>
#include <vector>

namespace arkanoid {

/*
World represents the entire game world. It is a rectangle area with (0,0) as
its top-left corner and (w, h) as its lower-right corner, where w and h are
its width and height. This rectangle defines the area of the entire
coordinate system that is visible to the player.
*/

class World {
public:
  // Implement the member functions listed below
  World(int32_t w, int32_t h, Ball b, Paddle p, std::vector<Brick> bs);

  int32_t getWidth() const;
  int32_t getHeight() const;

  /* Note: the following functions should all return copies of the data. This
  means that it is impossible to edit the World class using the returns from
  these functions:

  Ball b = myworld.getBall();  // OK!
  b.setCenter(10,4);         // Does not update the ball in myworld! */
  Ball getBall() const;
  Paddle getPaddle() const;
  std::vector<Brick> getBricks() const;

  /* Legality check on the state of the world: resolve illegal states and
  collisions according to the handout */
  bool isLegal() const;

  /* Run a single frame of the game logic, updating all the objects */
  void update(Input);

private:
  // Add any instance variables you need here
};

// The type of the exception that needs to be thrown when the game is over
class GameOverException : std::exception {};

// Additional logic to let std::cout work with World objects
std::ostream &operator<<(std::ostream &, const std::vector<Brick> &);
std::ostream &operator<<(std::ostream &, const World &);

} // namespace arkanoid
