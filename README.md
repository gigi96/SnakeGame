# Udacity C++ Nanodegree: Capstone final project

My Capstone project for the [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213) is an extension of the Snake game (https://github.com/udacity/CppND-Capstone-Hello-World.git).

<img src="snake_game.gif"/>

The following features have been added:
* statistics of player games:
  * a statistic is made up of a pair date-score;
  * statistics are saved in a txt file and showed in the console at the end of a game;
  * statistics are sorted by score;
  * the player can choose to save or not the result of the game
* obstacle objects:
  * an obstacle is added in the game in a random position in a similar way a food object is already inserted;
  * if the snake collides with an obstacle, snake's size and player's score are decremented;
  * if the snake size is equal to one and it collides with an obstacle, nothing happens

## Dependencies for Running Locally
* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* SDL2 >= 2.0
  * All installation instructions can be found [here](https://wiki.libsdl.org/Installation)
  >Note that for Linux, an `apt` or `apt-get` installation is preferred to building from source. 
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./SnakeGame`.

## Criteria

* Loops, Functions, I/O
  * The project demonstrates an understanding of C++ functions and control structures:
    * all the code uses different functions and control structures
  * The project reads data from a file and process the data, or the program writes data to a file:
    * the Game constructor and the Game::update_statistics() method read and write on a txt file
  * The project accepts user input and processes the input:
    * in the main.cpp there is a interaction with the end user
* Object Oriented Programming
  * The project uses Object Oriented Programming techniques:
    * all the code is made up of classes, with their declaration in the .h files and their implementation in the .cpp files
  * Classes use appropriate access specifiers for class members:
    * there are public and private members for each classes. Set and Get methods are use to access private attributes
  * Classes encapsulate behavior
  


## CC Attribution-ShareAlike 4.0 International


Shield: [![CC BY-SA 4.0][cc-by-sa-shield]][cc-by-sa]

This work is licensed under a
[Creative Commons Attribution-ShareAlike 4.0 International License][cc-by-sa].

[![CC BY-SA 4.0][cc-by-sa-image]][cc-by-sa]

[cc-by-sa]: http://creativecommons.org/licenses/by-sa/4.0/
[cc-by-sa-image]: https://licensebuttons.net/l/by-sa/4.0/88x31.png
[cc-by-sa-shield]: https://img.shields.io/badge/License-CC%20BY--SA%204.0-lightgrey.svg
