#include "snake.h"
#include <cmath>
#include <iostream>

void Snake::update() {
  SDL_Point prev_cell{
      static_cast<int>(head_x),
      static_cast<int>(
          head_y)};  // We first capture the head's cell before updating.
  update_head();
  SDL_Point current_cell{
      static_cast<int>(head_x),
      static_cast<int>(head_y)};  // Capture the head's cell after updating.

  // Update all of the body vector items if the snake head has moved to a new
  // cell.
  if (current_cell.x != prev_cell.x || current_cell.y != prev_cell.y) {
    update_body(current_cell, prev_cell);
  }
}

void Snake::update_head() {
  switch (direction) {
    case Direction::kUp:
      head_y -= speed;
      break;

    case Direction::kDown:
      head_y += speed;
      break;

    case Direction::kLeft:
      head_x -= speed;
      break;

    case Direction::kRight:
      head_x += speed;
      break;
  }

  // Wrap the Snake around to the beginning if going off of the screen.
  head_x = fmod(head_x + _grid_width, _grid_width);
  head_y = fmod(head_y + _grid_height, _grid_height);
}

void Snake::update_body(SDL_Point &current_head_cell, SDL_Point &prev_head_cell) 
{
  // Add previous head location to vector
  body.push_back(prev_head_cell);

  if (_growing == Status::NotGrowing) 
  {
    // Remove the tail from the vector.
    body.erase(body.begin());
  } 
  else if (_growing == Status::Decreasing)
  {
    // Remove the tail from the vector.
    body.erase(body.begin());
    if (size > 1)
    {
      body.erase(body.begin());
      size--;
    } 
    _growing = Status::NotGrowing;   
  }
  else 
  {
    _growing = Status::NotGrowing;
    size++;
  }

  // Check if the snake has died.
  for (auto const &item : body) {
    if (current_head_cell.x == item.x && current_head_cell.y == item.y) {
      alive = false;
    }
  }
}

void Snake::grow_body() { _growing = Status::Growing; }

// Inefficient method to check if cell is occupied by snake.
bool Snake::snake_cell(int x, int y) {
  if (x == static_cast<int>(head_x) && y == static_cast<int>(head_y)) {
    return true;
  }
  for (auto const &item : body) {
    if (x == item.x && y == item.y) {
      return true;
    }
  }
  return false;
}

void Snake::decrease_body() { _growing = Status::Decreasing; }