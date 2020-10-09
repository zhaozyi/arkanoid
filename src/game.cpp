#include "Ball.h"
#include "Brick.h"
#include "Input.h"
#include "LTimer.h"
#include "Paddle.h"
#include "World.h"

#include <SDL2/SDL.h>
#undef main
#include <iostream>
#include <stdio.h>
#include <vector>

/** Edit the lines below to alter the initial configuration of your game **/

// Sizes of various containers
constexpr int canvasSize =
    600; // Size (in pixels) of window this only affects
         // GUI size--all other properties depend on worldSize
constexpr int worldSize = 100; // Size of world (square)

// Initial conditions for ball. All sizes are relative to worldSize, not
// canvasSize
constexpr int ballInitX = 10;
constexpr int ballInitY = 50;
constexpr int radius = 5;
constexpr int ballInitVelocityX = 1;
constexpr int ballInitVelocityY = 1;

// Initial conditions for paddle
constexpr int paddleULInitX = 20;
constexpr int paddleULInitY = 90;
constexpr int paddleWidth = 20;
constexpr int paddleHeight = 5;
constexpr int paddleInitVelocity = 0;

// Set of initial bricks
std::vector<arkanoid::Brick> bricks;

/*****************************************************************************
 *****************************************************************************
 * Below this is rendering code--you should not need to touch it except to see
 * how it works or to fix bugs. Some code from http://lazyfoo.net/tutorials/SDL
 *****************************************************************************
 ******************************************************************************/

constexpr int SCREEN_WIDTH = canvasSize;
constexpr int SCREEN_HEIGHT = canvasSize;
constexpr int LINE_THICKNESS = 2;

// I am a naughty programmer and need to be punished for using globals like this
SDL_Window *window = NULL;         // Pointer to global SDL Window
SDL_Surface *screenSurface = NULL; // Pointer to canvas
SDL_Renderer *renderer = NULL;     // Pointer to rendering object
Uint32 outlineColor = 0;           // Color of outlines
int world_height = worldSize, world_width = worldSize;

// Constants used for FPS limiting. The game update is tied to the FPS, so on
// most modern systems, the game would move through 300-500 ticks in a second if
// we didn't cap the FPS at a certain value.
constexpr int FRAMES_PER_SECOND = 60;
constexpr int SCREEN_TICKS_PER_FRAME = 1000 / FRAMES_PER_SECOND;

/* Convert world coordinates to screen coordinates. Used to compensate for
 * the fact that world coordinates and pixel coordinates are different. Assumes
 * square world and square screen */
int toScreenSpace(int worldVal) {
  double ratio = SCREEN_HEIGHT / world_height;
  return static_cast<int>(ratio * worldVal);
}

// Boilerplate initialization code for the GUI
int initSDLWindow() {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    fprintf(stderr, "could not initialize sdl2: %s\n", SDL_GetError());
    return EXIT_FAILURE;
  }
  window = SDL_CreateWindow("hello_sdl2", SDL_WINDOWPOS_UNDEFINED,
                            SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                            SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

  if (window == nullptr) {
    fprintf(stderr, "could not create window: %s\n", SDL_GetError());
    return EXIT_FAILURE;
  }

  screenSurface = SDL_GetWindowSurface(window);
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  return EXIT_SUCCESS;
}

// Draw the ball as a series of rectangles
void drawBall(const arkanoid::Ball &b, Uint32 color) {
  int x = toScreenSpace(b.getCenter().x);
  int y = toScreenSpace(b.getCenter().y);
  int r = toScreenSpace(b.getRadius());

  // Draw constant number of rectangles to mock a circle
  // Calculate division points
  constexpr int num_divisions = 6;
  double divisions[num_divisions];
  for (int i = 0; i < num_divisions; i++) {
    divisions[i] = r / 2.0 + i * r / (2.0 * num_divisions);
  }
  // Draw rectangles
  SDL_Rect rect;
  for (int i = 0; i < num_divisions; i++) {
    int dx = static_cast<int>(divisions[i]);
    int dy = static_cast<int>(divisions[num_divisions - i - 1]);
    rect.x = x - dx;
    rect.y = y - dy;
    rect.w = 2 * dx;
    rect.h = 2 * dy;

    SDL_FillRect(screenSurface, &rect, color);
  }
}

// Draw paddle as a single rectangle of the appropriate size
void drawPaddle(const arkanoid::Paddle &p, Uint32 color) {
  SDL_Rect paddle;
  SDL_Rect paddle_outline;

  paddle.x = toScreenSpace(p.getUpperLeft().x);
  paddle.y = toScreenSpace(p.getUpperLeft().y);
  paddle.w = toScreenSpace(p.getLowerRight().x) - paddle.x;
  paddle.h = toScreenSpace(p.getLowerRight().y) - paddle.y;

  paddle_outline.x = paddle.x - LINE_THICKNESS;
  paddle_outline.y = paddle.y - LINE_THICKNESS;
  paddle_outline.w = paddle.w + 2 * LINE_THICKNESS;
  paddle_outline.h = paddle.h + 2 * LINE_THICKNESS;

  SDL_FillRect(screenSurface, &paddle, color);
}

// Draw bricks as a slightly smaller box than they actually are (so that) you
// can see a line between bricks--otherwise enough adjacent bricks form a solid
// square of color with no borders.
void drawBrick(const arkanoid::Brick &b, Uint32 color) {
  SDL_Rect brick;

  brick.x = toScreenSpace(b.getUpperLeft().x) + LINE_THICKNESS;
  brick.y = toScreenSpace(b.getUpperLeft().y) + LINE_THICKNESS;
  brick.w = toScreenSpace(b.getLowerRight().x) - brick.x;
  brick.h = toScreenSpace(b.getLowerRight().y) - brick.y;

  SDL_FillRect(screenSurface, &brick, color);
}

void drawAllBricks(const std::vector<arkanoid::Brick> &bricks, Uint32 color) {
  for (const auto &brick : bricks) {
    drawBrick(brick, color);
  }
}

arkanoid::Input calcInputFromKeys(bool leftHeld, bool rightHeld) {
  if (leftHeld && rightHeld) {
    return arkanoid::Input::None;
  } else if (leftHeld) {
    return arkanoid::Input::Left;
  } else if (rightHeld) {
    return arkanoid::Input::Right;
  } else {
    return arkanoid::Input::None;
  }
}

int main() {
  // Initialize our game variables and GUI. All globals should be set at this
  // point.
  if (initSDLWindow() == EXIT_FAILURE) {
    std::cerr << "Could not initialize a GUI window. Exiting with failure."
              << std::endl;
  }
  // Finish world setup--add bricks and init variables.
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      arkanoid::Point p {i * 20, j  * 5};
      bricks.push_back(arkanoid::Brick(p, 20, 5));
    }
  }
  arkanoid::Ball ball = {
      {ballInitX, ballInitY}, radius, {ballInitVelocityX, ballInitVelocityY}};
  arkanoid::Paddle paddle = {{paddleULInitX, paddleULInitY},
                             paddleWidth,
                             paddleHeight,
                             paddleInitVelocity};
  arkanoid::World world = {worldSize, worldSize, ball, paddle,
                           std::move(bricks)};
  if (!world.isLegal()) {
    std::cout << "[WARN]: The world is not starting in a legal state."
              << std::endl;
  }
  std::cout << world << std::endl;

  // Define a few colors for convenience for drawing later
  outlineColor = SDL_MapRGB(screenSurface->format, 0x00, 0x00, 0x00); // Global
  Uint32 sdl_red = SDL_MapRGB(screenSurface->format, 0xFF, 0x00, 0x00);
  Uint32 sdl_green = SDL_MapRGB(screenSurface->format, 0x00, 0xFF, 0x00);
  Uint32 sdl_yellow = SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0x00);

  // Prepare variables for main loop
  bool quit = false;      // Do we want to exit the program?
  bool leftHeld = false;  // Is left arrow key being held?
  bool rightHeld = false; // Is right arrow key being held?
  SDL_Event e;            // Used to handle event inputs
  LTimer fpsTimer;        // Used to implement FPS caps
  LTimer capTimer;
  int countedFrames = 0;
  fpsTimer.start();

  while (!quit) {
    // Handle left/right keypresses and exit events
    while (SDL_PollEvent(&e) != 0) {
      if (e.type == SDL_QUIT) {
        quit = true;
      } else if (e.type == SDL_KEYDOWN) {
        switch (e.key.keysym.sym) {
        case SDLK_LEFT:
          leftHeld = true;
          break;
        case SDLK_RIGHT:
          rightHeld = true;
          break;
        }
      } else if (e.type == SDL_KEYUP) {
        switch (e.key.keysym.sym) {
        case SDLK_LEFT:
          leftHeld = false;
          break;
        case SDLK_RIGHT:
          rightHeld = false;
          break;
        }
      }
    }

    // FPS calculations
    float avgFPS = countedFrames / (fpsTimer.getTicks() / 1000.f);
    if (avgFPS > 2000000) {
      avgFPS = 0;
    }

    // Update game state based on user input
    arkanoid::Input input = calcInputFromKeys(leftHeld, rightHeld);
    try {
      world.update(input); // THE ONLY PIECE YOU NEED TO GET WORKING
    } catch (arkanoid::GameOverException) { // World threw game over
      SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Game Over!",
                               "Sorry, you lost :(", window);
      quit = true;
    } catch (std::exception) { // World crashed in some other way
      SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Ruh Roh Scooby...",
                               "Your program threw some sort of error.",
                               window);
      quit = true;
    }

    SDL_FillRect(screenSurface, NULL, outlineColor); // background color
    drawAllBricks(world.getBricks(), sdl_yellow);
    drawPaddle(world.getPaddle(), sdl_green);
    drawBall(world.getBall(), sdl_red);
    SDL_UpdateWindowSurface(window);

    // Finally, see how much time this took and delay if our FPS would go too
    // high
    ++countedFrames;
    int frameTicks = capTimer.getTicks();
    if (frameTicks < SCREEN_TICKS_PER_FRAME) {
      // Wait remaining time
      SDL_Delay(SCREEN_TICKS_PER_FRAME - frameTicks);
    }
  }

  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}
