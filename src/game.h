#ifndef GAME_H
#define GAME_H

#include <random>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"
#include <ctime>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>

class Game
{
public:
  Game(std::size_t grid_width, std::size_t grid_height);
  void run(Controller const &controller, Renderer &renderer,
           std::size_t target_frame_duration);
  int get_score() const;
  int get_size() const;
  void update_statistics();

private:
  Snake _snake;
  SDL_Point _food;
  SDL_Point _obstacle;

  std::random_device _dev;
  std::mt19937 _engine;
  std::uniform_int_distribution<int> _random_w;
  std::uniform_int_distribution<int> _random_h;

  int _score{0};
  time_t _date;
  std::vector<std::pair<std::string, int>> _statistics;
  std::fstream _statistics_file;//("statistics.txt", std::ios::in | std::ios::out | std::ios::app);

  void place_food();
  void update();
  static bool sort_by_second(const std::pair<std::string,int> &a, const std::pair<std::string,int> &b);
  void place_obstacle();
};

#endif