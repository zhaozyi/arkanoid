#include "World.h"

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace arkanoid;

int main() {
  // Read in 5 numbers representing the ball config
  int32_t ballX, ballY, ballR, ballVX, ballVY;
  std::cin >> ballX >> ballY >> ballR >> ballVX >> ballVY;
  Ball ball = {{ballX, ballY}, ballR, {ballVX, ballVY}};

  // Read in 5 numbers representing the paddle
  int32_t padULX, padULY, padW, padH, padV;
  std::cin >> padULX >> padULY >> padW >> padH >> padV;
  Paddle paddle = {{padULX, padULY}, padW, padH, padV};

  int numBricks;
  std::cin >> numBricks;
  std::vector<Brick> bricks;

  // Read in our bricks, one at a time
  for (int i = 0; i < numBricks; i++) {
    int brickULX, brickULY, brickW, brickH;
    std::cin >> brickULX >> brickULY >> brickW >> brickH;
    bricks.emplace_back(Point{brickULX, brickULY}, brickW, brickH);
  }

  // Read in the height and width of the world, as well as number of rounds
  int32_t worldWidth, worldHeight, numTicks;
  std::cin >> worldWidth >> worldHeight >> numTicks;

  // Finally, read in the inputs on each round, where -1 = left, 0 = none, +1 =
  // right
  std::vector<arkanoid::Input> inputs;
  std::string s;

  // Sponge any newlines leftover in cin
  while(std::all_of(s.begin(), s.end(), isspace)){
    std::getline(std::cin, s);
  }

  for (int i = 0; i < numTicks; i++) {
    // Inverting order here because s already has the first line from above loop
    int inp = std::stoi(s);
    std::getline(std::cin, s);
    if (inp == -1) {
      inputs.push_back(arkanoid::Input::Left);
    }
    if (inp == 0) {
      inputs.push_back(arkanoid::Input::None);
    }
    if (inp == 1) {
      inputs.push_back(arkanoid::Input::Right);
    }
  }

  // A WHOLE NEW WOOOOORRRRLLLLLDDDDD
  World world = {worldWidth, worldHeight, ball, paddle, std::move(bricks)};

  // Test our isLegal function
  if ( numTicks <= 0){
    std::cout << "isLegal = " << world.isLegal() << std::endl;
  }

  // Run the world, printing its state every frame
  int frameNum = 0;
  for (int i = 0; i < numTicks; i++) {
    try {
      world.update(inputs[i]);
    } catch (const GameOverException &E) {
      std::cout << "Game ended: game over, on frame " << frameNum << std::endl;
      break;
    }
    frameNum++;
  }
  std::cout << world << std::endl;
  return 0;
}
