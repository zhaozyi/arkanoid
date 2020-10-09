#pragma once
#include <SDL2/SDL.h>
#include <cstdint>

// YOU DO NOT NEED TO EDIT THIS FILE. It is only used by the GUI code.

// From http://lazyfoo.net/tutorials/SDL/25_capping_frame_rate/index.php
// Used to implement framerate limiting in the GUI--the game speed is tied to
// the framerate, and this game will typically run 600+ FPS without this

class LTimer {
public:
  // Initializes variables
  LTimer();

  // The various clock actions
  void start();
  void stop();
  void pause();
  void unpause();

  // Gets the timer's time
  uint32_t getTicks();

  // Checks the status of the timer
  bool isStarted();
  bool isPaused();

private:
  // The clock time when the timer started
  uint32_t mStartTicks;

  // The ticks stored when the timer was paused
  uint32_t mPausedTicks;

  // The timer status
  bool mPaused;
  bool mStarted;
};
