#ifndef SNAKE_H
#define SNAKE_H

#include <vector>
#include "SDL.h"

class Snake {
 public:
  enum class Direction { kUp, kDown, kLeft, kRight };
  enum class Status { NotGrowing, Growing, Decreasing};

  Snake(int grid_width, int grid_height)
      : _grid_width(grid_width),
        _grid_height(grid_height),
        head_x(grid_width / 2),
        head_y(grid_height / 2) {}

  void update();

  void grow_body();
  bool snake_cell(int x, int y);
  void decrease_body();

  Direction direction = Direction::kUp;

  float speed{0.1f};
  int size{1};
  bool alive{true};
  float head_x;
  float head_y;
  std::vector<SDL_Point> body;

 private:
  void update_head();
  void update_body(SDL_Point &current_cell, SDL_Point &prev_cell);

  Status _growing{Status::NotGrowing};
  int _grid_width;
  int _grid_height;
};

#endif