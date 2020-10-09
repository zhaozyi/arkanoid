Project 1: Arkanoid
==========================

# EDIT THIS SECTION FOR GENERAL SUBMISSION INFORMATION

* YOUR NAME
* YOUR EID
* THE NUMBER OF SLIP DAYS YOU **ARE GOING TO** USE ON THIS PROJECT
* THE NUMBER OF SLIP DAYS YOU **HAVE USED** IN THE COURSE SO FAR.

## IN THIS SUBSECTION, FILL ANY STRETCH GOALS YOU ATTEMPTED, AND HOW TO ENABLE THEM IN YOUR CODE

# Introduction

**out of 100 points, 115 points hard cap**

In this project, you will implement the game logic for a game called Arkanoid, 
which is a simple clone of
[Breakout](https://en.wikipedia.org/wiki/Breakout_(video_game)). The player
controls a paddle at the bottom of the screen to bounce a ball around and
eliminate as many bricks as possible. You will implement such a game for
this assignment.

# Description

Video games like Arkanoid are usually implemented with the [game
loop](http://gameprogrammingpatterns.com/game-loop.html) pattern. The
main function of the program consists of a simple loop that looks like
this:

```cpp
	while (!gameOver) {
		playerInput = readInput();
		world.update(playerInput);
		render(world);
	}
```

Every iteration of the loop consists of three steps: (1) read the player’s
input, (2) update the game world according to the input, and (3) render
the game world onto the screen. We will primarily focus on game updates
(step 2) in this project.

# Directions and Hints

## Download and build the skeleton project

Use `git clone` to get a local copy of your git repository hosted on GitHub
Classroom. Take a look at the skeleton code. There is a `src/` directory,
which includes several headers + code files, as well as CMakeLists.txt at the
root of your git repository, which encodes rules for how to compile the
project.

You can build the code with the following steps:
1. Create a `build` directory (Not necessary to be this name but this is the
   the most common choice);
2. Under the `build` directory, run `cmake ..`. This will create the Makefile
   to build the project;
   - Alternatively, you can generate Visual Studio project file with `-G
     'Visual Studio 16 2019'`, or Xcode project file with `-G Xcode`
3. Run `make` to actually build the project.

**Read through the skeleton code before starting**. C++ convention holds that
header files should contain high-level comments about what functions/classes
do and how they fit in to the program, while cpp files should contain
implementation details. We will use this convention for the rest of the class:
read the headers to discover what functions should do and why, and instructions
for trickier implementations will be in the cpp files.

## Modifying the Code

The starter code you have been given represents the bare minimum of what you
must implement for a working project (at least, as far as the autograder is
concerned). However, you are *not* restricted to using just the provided methods.

Other students who have done these projects have noted that, e.g. it's really
annoying to have to repeatedly calculate the width of a `Paddle`. If you
find yourself thinking "gosh, it's really annoying that I have to do `X` over 
and over again", you should probably look into some way of automating that
(functions are a good one). Similarly, the classes do not have any variables,
which makes it very difficult to store object data. You should definitely 
fix this.

However, there are some things you should not change. While you should not
modify any of the function signatures in the skeleton code (i.e. any functions
you were given), it is **vital** that you do not edit any printing functions
in the skeleton! This printing code will be used to evaluate the correctness
of your implementation: any changes could immediately render your entire project
"wrong" from the perspective of the autograder.

## Implementing Game Updates

Once you have a rough idea of how all the pieces fit together, you can start
writing code. All functions that you need to implement have 
`// TODO: Implement me` above them in the code. Some will have additional
comments (either in the cpp or in the header) that explain how they should work.

I recommend implementing the functions in `Ball`, `Brick`, and `Paddle` before 
you start implementing the functions in `World`. If you accidentally delete the
comment-instructions, you can restore them from version control (you *are* using
version control, right?) or find a backup set of instructions [here](details.md).

If you have a question about various containers (e.g. vector), check
[cppreference.com](http://cppreference.com). Don’t be afraid to make a
small program just to try out some code. The compiler is your friend.

## Style Considerations

The larger your programs get, the easier it is to make mistakes, and the more
work you must put into guarding against them.

In this assignment, you should take particular care to avoid using global
variables, and make sure that your implementations are completely separate from
your interfaces: make sure your class member definitions are only in `.cc`
or `.cpp` files. (This is VERY different from Java!)

# Evaluation

While Arkanoid is a game and is best evaluated by the good old-fashioned MK1
eyeball, I (unfortunately) do not have the time to attempt to play and trigger 
edge cases in this many games. Therefore, your evaluation will be based entirely
on text-based measures: the testing framework will feed your program a string
that represents the game to simulate, and your program will print a string
that represents the new game state after the simulation.

Within the `main` function, there should already be some code that reads an
input string and sets up a game. If you'd like, you can use that text input 
functionality to test your game, or you can set up your own tests.

# Playing Arkanoid

Once you implement the classes for the game, you can play it using a GUI with
the following steps:

```
cd build
make game
./game
```

In order for the code to work, you need a GUI and an installed version of
libSDL2. The easiest way to get this is to use (physically) one of the lab
machines, though it can also be built on Linux/macOS/Windows if you install the
libraries yourself.

# Submission and Grading

Make sure to read the [general project grading rules](https://www.cs.utexas.edu/~zxy/teaching/cs105c/f20/logistics/grading/).

You will submit the project through `git push` to Github Classroom.
I must be able to do the following in an automated manner:

```
	git clone <your repo>
	cd <the repo name>
	rm -rf build
	mkdir build
	cd build
	cmake ..
	make
	./arkanoid
	<test input>
```

Make sure you do not change any of the provided printing functions, or your
code may break the autograder.

Make sure you can build your code by cloning your repository to another
places, in case of forgetting committing any changes to your local git repo,
or pushing changes to GitHub.

If you have any questions about the assignment, please ask on Piazza.

# Stretch Objectives
If you finish the project early and have time to burn, you might consider trying
one of these stretch goals. They will give you small amounts of bonus points,
capped at 15 points.

Fair warning: these stretch goals are *not* easy, and are more designed so that
those of you who want to learn a little more about the weird fringes of C++ can 
cut your teeth. You will get many more points from implementing the main project
well and testing it thoroughly than you will get from these bonuses.

If you attempt these, you **must** make sure your code still compiles on the
lab machines and does not interfere with the correctness of the results. For 
this project, you will have to add new files and new rules to the Makefile.
Make sure you document them in your README!

## Stretch A: Better Game Experience (5pts)

The current update rules for the paddle are a little boring: the ball will
always bounce away at the same angle no matter where we hit the paddle. A more
interesting update (which gives the user more control) is to split the paddle
into a number of segments. If the ball hits close to the center, it is reflected
normally, while if it hits one of the outer segments, it reflects more in that
direction.

In addition, if you try the game, you may notice that we have no ball-brick
bounces. This was made to simplify the grading, but it doesn't make for a
great game. Make the ball bounce when it hits a brick.

Implement this scheme in your world update. In your README, explain exactly
what scheme you used (how do you determine which section of the paddle the ball
hit? How much did you decide to deflect the ball by? How do you implement the
reflection? How many sections are on your paddle?), and how I can test the
result.

Remember that you must not change the behavior of your original solution! A 
solution here is to make a second executable (e.g. `arkanoid-better`) that
has this behavior.

## Stretch B: Make things pretty (up to 5pts)

This is for those of you who want to explore graphics code a little more.
Edit `game.cpp` to make the game prettier. There's no set objective here: pick
something you think will look cool and implement it. The graphics code uses
`libsdl2`--you can find their wiki at [https://wiki.libsdl.org/](https://wiki.libsdl.org/).

For a rough idea of point values, something like varying colors on the bricks
will be worth one point, while a cool-looking particle trail system on the ball 
might be worth 3.

Explain in your README exactly what you chose to implement, and how to enable
those changes (if relevant).

## Stretch C: Object Pooling (10pts)

Implement a system where every 20 seconds (~1200 frames), a new wave of bricks
comes down from the top, pushing existing bricks down. The game now ends if the
ball goes off the bottom edge of the screen **OR** if a brick makes it to the
bottom edge.

In practice, most games do *not* want to allocate a bunch of new rectangles when
drawing a new line, because memory management is expensive. If you have too
many rectangles to allocate, the game may noticeably freeze.[^1] To get
around this, many actual games end up using [object pooling](https://www.raywenderlich.com/847-object-pooling-in-unity),
where there's a fixed-size pool of objects already allocated at the start, and
you simply re-use them as needed.

You must implement this line-of-bricks system **without** making any calls to
memory allocation. Things like creating a vector or using `new` are strictly
forbidden. You may assume that you will have no more than 1024 bricks on screen
at any point in time.

Explain in your README how to enable this new mode of your game. I will test it
by running it in a debugger and intercepting any calls to `malloc()`. There will
be a few calls made by library code, but if there are any calls coming from your
code, you will lose points on this stretch objective.

* * * * * *

[^1]: If you use a language like Java where the allocation is instant, you end up paying the cost during garbage collection instead.
