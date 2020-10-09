Arkanoid: Additional details
=========

While details of what you need to implement for this project are in the C++
files, here is a copy in case you need it. The main project page can be found
[here](instructions.md).

## Overview of Classes

You will be modifying the following classes:

  - `Point` represents a 2D point on the screen[^1].

  - `Velocity` represents a 2D vector that indicates the direction and
    speed of movement.

  - `Ball` represents the bouncing ball. It has a circle shape and thus
    can be located by a `Point` that represents its center and an
    integer that represents its radius. We also need to associate a
    `Velocity` to the ball since it can move freely in the game world.

  - `Paddle` represents the paddle that the player controls. It has a
    rectangle shape and thus can be represented by a `Point` for the
    location of its upper-left corner and a pair `(w, h)` for its
    width and height. The paddle is also movable but can only do so
    horizontally, so it is sufficient to represent its velocity with a
    single integer.

  - `Brick` represents a brick that the player has to destroy. Like the
    paddle, it also has a rectangle shape so we represent it in the same
    way, but without a velocity.

  - `World` represents the entire game world. It is a rectangle area
    with `(0,0)` as its top-left corner and `(w, h)` as its
    lower-right corner, where `w` and `h` are its width and height.
    This rectangle defines the area of the entire coordinate system that
    is visible to the player.

## Functions to Implement

Complete the member functions listed below. The code you write in this
section is going to serve as base utilities for the next section.

  - `Ball`

      - Implement the constructor of the `Ball` class. The constructor
        takes three parameters: the center point of the ball, the radius
        of the ball, and the velocity of the ball.

      - Implement the `getCenter()`, `getRadius()`, and `getVelocity()`
        member functions, which returns the center point, the radius,
        and the velocity of the ball, respectively.

  - `Paddle`

      - Implement the constructor of the `Paddle` class. The constructor
        takes three parameters: the upper-left corner of the paddle, the
        width of the paddle, the height of the paddle, and the velocity
        of the paddle.

      - Implement the `getUpperLeft()` and `getLowerRight()` member
        functions, which returns the upper-left corner and the
        lower-right corner of the paddle, respectively.

  - `Brick`

      - A brick is like a paddle without velocity. Implement its
        constructor, `getUpperLeft()` and `getLowerRight()` member
        functions similarly to the `Paddle` class.

  - `World`

      - Implement the `World` constructor. There are 5 parameters in the
        constructor: its width, its height, a ball, a paddle, and a
        vector of bricks.

      - Implement the `get()` functions for each of the 5 parameters.

### `World::isLegal()`

Users of the `World` class are able to use the class’ constructor to
create arbitrary game world, including worlds that contain an illegal
game states. For example, there is nothing that prevents the user from
constructing a world without any bricks, or a world with a ball of
velocity zero. The `isLegal()` member function should detect such
illegal initial game states. Specifically, it does the following check:

  - There should be at least one brick in the world.

  - The ball must have a nonzero velocity.

  - All entities (ball, paddle, and bricks) must locate completely
    inside the boundaries of the world.

  - Entities must not collide with one another.[^2]

### `World::update()`

Given a legal `World` object, the final task is to write the update
logic for the game: `World::update()`. The function takes the user input
as a parameter, which is an scoped enum that has three possibilities:
`Input::None` (player does not press any key), `Input::Left` (player
wants to move the paddle to the left), `Input::Right` (player wants to
move the paddle to the right). Based on the user input, it should update
the internal state of the `World` object:

  1. First, the paddle moves. If the original location of the paddle is
    `(x, y)`, the new location would be `(x + v, y)`, where `v` is
    the paddle’s velocity. However, if the paddle would move beyond the
    left (or right) boundary of the game world, you need to keep it
    inside the world and align it to the left (or right, respectively)
    world boundary.

  2. Next, the paddle’s velocity changes according to the user input.

      - If the input is `Input::None`, set the velocity to zero.

      - If the input is `Input::Left`, set the velocity to
        `-Paddle::DefaultVelocity`.

      - If the input is `Input::Right`, set the velocity to
        `Paddle::DefaultVelocity`.

  3. Then, the ball moves. If the original location of the ball is
  `(x, y)`, the new location would be `(x + v_x, y + v_y)`, where
  `v_x` and `v_y` are the ball’s horizontal velocity and vertical
  velocity, respectively.
  
     After this step, it is OK if the ball moves to an illegal position
     (e.g. it goes outside of the game world, or it overlaps with either
     the paddle or some bricks). In the next step, we will fix that by
     changing the ball’s velocity in such a way that will move the ball
     out of the illegal position in the next couple of frames.

  4. Next, the ball’s velocity changes.

      - If the ball collides with or goes beyond the left boundary of
        the world, set its horizontal velocity to
        `Ball::DefaultHorizontalVelocity`.

      - If the ball collides with or goes beyond the right boundary of
        the world, set its horizontal velocity to
        `-Ball::DefaultHorizontalVelocity`.

      - If the ball collides with or goes beyond the upper boundary of
        the world, set its vertical velocity to
        `Ball::DefaultVerticalVelocity`.

      - If the ball collides with the paddle, set its vertical velocity
        to `-Ball::DefaultVerticalVelocity`.

      - If the ball collides with or goes beyond the lower boundary of
        the world, the game is over. We handle this case by throwing an
        exception: `throw GameOverException();`[^3]

  - Finally, remove all bricks that collide with the ball.

[^1]: In our coordinate system, the origin `(0,0)` is located on the top-left corner of the screen

[^2]:  For collision detection, view all entities (including the ball) as a box, and use the simple [`Axis-Aligned Bounding Box`](https://developer.mozilla.org/en-US/docs/Games/Techniques/2D_collision_detection) algorithm. Note that according to the algorithm, if the bounding boxes of two game entities intersect only through an edge or through a vertex then this does not count as a collision.

[^3]:  We use exceptions just to make the task simple. Please be aware that this is not how `C++` exceptions are supposed to be used. You would not want to do this in real-world game development.
