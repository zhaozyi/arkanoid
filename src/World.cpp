#include "World.h"

#include <ostream>


namespace arkanoid {

// TODO: Implement me
World::World(int32_t w, int32_t h, Ball b, Paddle p, std::vector<Brick> bs) : 
worldBall(b.getCenter(), b.getRadius(), b.getVelocity()),
worldPaddle(p.getUpperLeft(), p.getPaddleWidth(), p.getPaddleHeight(), p.getVelocity()),
worldBS(bs.begin(), bs.end())
{
  /* Arguments:
    w: width of the world
    h: height of the world
    b: a ball
    p: a paddle
    bs: a vector of bricks
  */
  worldWidth = w;
  worldHeight = h;
}

// ----------ADDED FUNCTIONS------------
/* check if ball goes outside the world */
bool World::ballExceeds() const {
  Point currBallCenter = worldBall.getCenter();
  int32_t currBallRadius = worldBall.getRadius();
  int32_t xLeftBound = currBallRadius;
  int32_t xRightBound = worldWidth - currBallRadius;
  int32_t yUpperBound = currBallRadius;
  int32_t yLowerBound = worldHeight - currBallRadius;
  bool exceed = (currBallCenter.x < xLeftBound) || (currBallCenter.x > xRightBound) 
  || (currBallCenter.y > yLowerBound) || (currBallCenter.y < yUpperBound);
  return exceed ? true : false;
}

/* check if paddle lies outside the world*/
bool World::paddleExceeds() const {
  Point currPaddleUpperLeftCorner = worldPaddle.getUpperLeft();
  int32_t xRightBound = worldWidth - worldPaddle.getPaddleWidth();
  int32_t yLowerBound = worldHeight - worldPaddle.getPaddleHeight();
  bool exceed = (currPaddleUpperLeftCorner.x < 0) || (currPaddleUpperLeftCorner.x > xRightBound) 
  || (currPaddleUpperLeftCorner.y < 0) || (currPaddleUpperLeftCorner.y > yLowerBound);
  return exceed ? true : false;  
}

/* check if the brick lies outside the world */
bool World::brickExceeds() const {
  for (auto currBrick : worldBS) {
    Point currBrickUpperLeftCorner = currBrick.getUpperLeft();
    int32_t xRightBound = worldWidth - currBrick.getBrickWidth();
    int32_t yLowerBound = worldWidth - currBrick.getBrickHeight();
    bool exceed = (currBrickUpperLeftCorner.x < 0) || (currBrickUpperLeftCorner.x > xRightBound) 
    || (currBrickUpperLeftCorner.y < 0) || (currBrickUpperLeftCorner.y > yLowerBound);
    if (exceed) {
      return true;
    }
  }
  return false;
}

/*
  Any rectangle collision detection:
  if (rect1.x < rect2.x + rect2.width &&
   rect1.x + rect1.width > rect2.x &&
   rect1.y < rect2.y + rect2.height &&
   rect1.y + rect1.height > rect2.y) {
    // collision detected!
  }
*/
bool World::hasCollision(Point p1, int32_t w1, int32_t h1, Point p2, int32_t w2, int32_t h2) const {
  if ((p1.x < p2.x + w2) && (p1.x + w1 > p2.x) && (p1.y < p2.y + h2) && (p1.y + h1 > p2.y)) {
    return true;
  }
  return false;
}




// TODO: Implement me
int32_t World::getWidth() const { return worldWidth; }

// TODO: Implement me
int32_t World::getHeight() const { return worldHeight; }

// TODO: Implement me
Ball World::getBall() const { return Ball(worldBall.getCenter(), worldBall.getRadius(), worldBall.getVelocity()); }

// TODO: Implement me
Paddle World::getPaddle() const { 
  return Paddle(worldPaddle.getUpperLeft(), worldPaddle.getPaddleWidth(), worldPaddle.getPaddleHeight(), worldPaddle.getVelocity());
}

// TODO: Implement me
std::vector<Brick> World::getBricks() const { return std::vector<Brick>(worldBS.begin(), worldBS.end()); }


// TODO: Implement me
bool World::isLegal() const {
  // Placeholder return--remove when finished
  //return false;

  /* Users of this class are able to use the class’s constructor to
  create arbitrary game worlds, including worlds that contain an illegal
  game states. For example, there is nothing that prevents the user from
  constructing a world without any bricks, or a world with a ball of
  velocity zero. The `isLegal()` member function should detect such
  illegal initial game states. Specifically, it does the following checks: */

  /*
  There should be at least one brick in the world.
  */
  if (worldBS.size() < 1) {
    return false;
  }

  /*
  The ball must have a nonzero velocity.
  */
  Velocity currBallVelocity = worldBall.getVelocity();
  if (currBallVelocity.vx == 0 && currBallVelocity.vy == 0) {
    return false;
  }

  /*
  All entities(ball, paddle, and bricks) must be *entirely* within the boundary
  of the world. This means that if one corner of a brick is within the world,
  but the other corner is not, it is out-of-bounds. Treat the ball as a square
  box for the purposes of this check.
  */
  if (ballExceeds() || paddleExceeds() || brickExceeds()) {
    return false;
  }

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
  Point ballUpperLeft = {worldBall.getCenter().x - worldBall.getRadius(), worldBall.getCenter().y - worldBall.getRadius()};
  int32_t ballWidth = worldBall.getRadius() * 2;
  int32_t ballHeight = worldBall.getRadius() * 2;

  Point paddleUpperLeft = worldPaddle.getUpperLeft();
  int32_t paddleWidth = worldPaddle.getPaddleWidth();
  int32_t paddleHeight = worldPaddle.getPaddleHeight();

  // return false if ball collides with paddle, else not
  if (hasCollision(ballUpperLeft, ballWidth, ballHeight, paddleUpperLeft, paddleWidth, paddleHeight)) {
    return false;
  }

  // return false if any brick collides with ball or paddle, else not
  for (auto currBrick : worldBS) {
    Point brickUpperLeft = currBrick.getUpperLeft();
    int32_t brickWidth = currBrick.getBrickWidth();
    int32_t brickHeight = currBrick.getBrickHeight();
    bool collideWithBall = hasCollision(ballUpperLeft, ballWidth, ballHeight, brickUpperLeft, brickWidth, brickHeight);
    bool collideWithPaddle = hasCollision(paddleUpperLeft, paddleWidth, paddleHeight, brickUpperLeft, brickWidth, brickHeight);
    if (collideWithBall || collideWithPaddle) {
      return false;
    }
  }

  // return false if brick and brick collide, else not
  for (int i = 0; i < worldBS.size(); i++) {
    Point p1 = worldBS[i].getUpperLeft();
    int32_t w1 = worldBS[i].getBrickWidth();
    int32_t h1 = worldBS[i].getBrickHeight();
    for (int j = i + 1; j < worldBS.size(); j++) {
      Point p2 = worldBS[j].getUpperLeft();
      int32_t w2 = worldBS[j].getBrickWidth();
      int32_t h2 = worldBS[j].getBrickHeight();
      if (hasCollision(p1, w1, h1, p2, w2, h2)) {
        return false;
      }
    }
  }
  return true;
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
  Point newLocation = {worldPaddle.getUpperLeft().x + worldPaddle.getVelocity(), worldPaddle.getUpperLeft().y};
  int32_t xRightBound = worldWidth - worldPaddle.getPaddleWidth();
  if (newLocation.x < 0) {
    worldPaddle.setLocation(Point{0, newLocation.y});
  } else if (newLocation.x > xRightBound) {
    worldPaddle.setLocation(Point{xRightBound, newLocation.y});
  } else {
    worldPaddle.setLocation(newLocation);
  }
  /*
  Next, the paddle’s velocity changes according to the user input.
    - If the input is Input::None, set the velocity to zero.
    - If the input is Input::Left, set the velocity to -Paddle::DefaultVelocity.
    - If the input is Input::Right, set the velocity to Paddle::DefaultVelocity.
  */
  if (in == arkanoid::Input::None) {
    worldPaddle.setVelocity(Velocity{0, 0});
  } else if (in == arkanoid::Input::Left) {
    worldPaddle.setVelocity(Velocity{-Paddle::DefaultVelocity, 0});
  } else if (in == arkanoid::Input::Right) {
    worldPaddle.setVelocity(Velocity{Paddle::DefaultVelocity, 0});
  }

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
  Velocity currBallVelocity = worldBall.getVelocity();
  Point newBallCenter = {worldBall.getCenter().x + currBallVelocity.vx, worldBall.getCenter().y + currBallVelocity.vy};
  worldBall.setLocation(newBallCenter);


  /*
  Now we resolve any collisions or illegal states that may have occurred from
  the previous step. Order of collision resolution is important!
  */
  int32_t ballRadius = worldBall.getRadius();
  int32_t leftBound = ballRadius;
  int32_t rightBound = worldWidth - ballRadius;
  int32_t upperBound = ballRadius;
  int32_t lowerBound = worldHeight - ballRadius;

  /* If the ball collides with or goes beyond the left boundary of the world,
     set itshorizontal velocity to Ball::DefaultHorizontalVelocity. */
  if (newBallCenter.x < leftBound) {
    worldBall.setVelocity(Velocity{Ball::DefaultHorizontalVelocity, currBallVelocity.vy});
  }

  /* If the ball collides with or goes beyond the right boundary of the world,
     set its horizontal velocity to -Ball::DefaultHorizontalVelocity.*/
  if (newBallCenter.x > rightBound) {
    worldBall.setVelocity(Velocity{-Ball::DefaultVerticalVelocity, currBallVelocity.vy});
  }
  /* If the ball collides with or goes beyond the upper boundary of the world,
  set its vertical velocity toBall::DefaultVerticalVelocity */
  if (newBallCenter.y < upperBound) {
    worldBall.setVelocity(Velocity{currBallVelocity.vx, Ball::DefaultVerticalVelocity});
  }

  /* If the ball collides with the paddle, set its vertical velocity to
     -Ball::DefaultVerticalVelocity. */
  Point ballUpperLeft = {newBallCenter.x - ballRadius, newBallCenter.y - ballRadius};
  int32_t w1 = 2 * ballRadius;
  int32_t h1 = 2 * ballRadius;
  Point paddleUpperLeft = worldPaddle.getUpperLeft();
  int32_t w2 = worldPaddle.getPaddleWidth();
  int32_t h2 = worldPaddle.getPaddleHeight();
  if (hasCollision(ballUpperLeft, w1, h1, paddleUpperLeft, w2, h2)) {
    worldBall.setVelocity(Velocity{currBallVelocity.vx, -Ball::DefaultVerticalVelocity});
  }

  /* If the ball collides with or goes beyond the lower boundary of the world,
     the game is over. We handle this case by throwing an exception:
     throw GameOverException().

     Please do not actually do this for an actual game--we use exceptions here
     to keep things simple, but they are definitely not designed to be used like
     this. */
  if (newBallCenter.y > lowerBound) {
    throw GameOverException();
  }

  /*
    Remove all bricks that collide with a ball. Instead of trying to hand-code
    this yourself, I suggest looking at std::remove_if in <algorithm> */
  for (int i = 0; i < worldBS.size(); i++) {
    Point brickUpperLeft = worldBS[i].getUpperLeft();
    int32_t width = worldBS[i].getBrickWidth();
    int32_t height = worldBS[i].getBrickHeight();
    if (hasCollision(ballUpperLeft, w1, h1, brickUpperLeft, width, height)) {
      worldBS.erase(worldBS.begin() + i);
      i--;
    }
  }
  
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
