#include "game.h"
#include "SDL.h"
#include <iomanip>
#include <chrono>

Game::Game(std::size_t grid_width, std::size_t grid_height)
    : _snake(grid_width, grid_height),
      _engine(_dev()),
      _random_w(0, static_cast<int>(grid_width - 1)),
      _random_h(0, static_cast<int>(grid_height - 1))
{
  place_food();

  _statistics_file.open("../resources/statistics.txt", std::ios::in | std::ios::out);
  if(_statistics_file.is_open())
  {
    std::string line, date, score;
    std::tm tm {};
    while(getline(_statistics_file, line))
    {
      date = line.substr(0, line.find("|")); // token is "scott"
      score = line.substr(line.find("|") + 1, line.back());          
      std::istringstream s_date(date);
      s_date >> std::get_time(&tm, "%Y-%b-%d %H:%M:%S"); 

      _statistics.push_back({date, std::stoi(score)});
    }
    _statistics_file.close();
  }
  else 
  {
    _statistics_file.open("../resources/statistics.txt", std::ios::out);
    _statistics_file <<"\n";
    _statistics_file.close();
  }
}

void Game::run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;

  while (running) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, _snake);
    update();
    renderer.Render(_snake, _food, _obstacle);

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(_score, frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}

void Game::place_food()
{
  int x, y;
  while (true) {
    x = _random_w(_engine);
    y = _random_h(_engine);
    // Check that the location is not occupied by a snake item 
    // and by an obstacle before placing food.
    if (!_snake.snake_cell(x, y) && (x != _obstacle.x && y != _obstacle.y)) 
    {
      _food.x = x;
      _food.y = y;
      return;
    }
  }
}

void Game::update()
{
  if (!_snake.alive) return;

  _snake.update();

  int new_x = static_cast<int>(_snake.head_x);
  int new_y = static_cast<int>(_snake.head_y);

  // Check if there's food over here
  if (_food.x == new_x && _food.y == new_y)
  {
    _score++;
    place_food();
    place_obstacle();
    // Grow snake and increase speed.
    _snake.grow_body();
    _snake.speed += 0.02;
  }

  // Check if there's obstacle over here
  if (_obstacle.x == new_x && _obstacle.y == new_y) 
  {
    if (_score > 0)
    {
      _score--;
      _snake.decrease_body();
    }    
    place_obstacle();
  }
}

int Game::get_score() const { return _score; }
int Game::get_size() const { return _snake.size; }

void Game::update_statistics()
{
  time_t now = time(0);   
  tm *ltm = localtime(&now);
  std::istringstream stream;
  std::stringstream ostream;
  stream>>std::get_time(ltm, "%Y-%b-%d %H:%M:%S");
  std::string s_date;
  ostream << std::put_time(ltm, "%Y-%b-%d %H:%M:%S");
  s_date = ostream.str();  

  //std::cout<<"\n s_date"<<s_date;
  _statistics.push_back({s_date, _score});
  std::sort(_statistics.begin(), _statistics.end(), sort_by_second);

  _statistics_file.open("../resources/statistics.txt", std::ios::in | std::ios::out);

  for (const auto& [key, value] : _statistics)
  {
    _statistics_file << key << "|" << value <<"\n";
    std::cout<<"score: "<<value<<"\t date: "<<key<<"\n";
  }

}

bool Game::sort_by_second(const std::pair<std::string,int> &a, const std::pair<std::string,int> &b)
{
    return (a.second > b.second);
}

void Game::place_obstacle()
{
  int x, y;
  while (true) {
    x = _random_w(_engine);
    y = _random_h(_engine);
    // Check that the location is not occupied by a snake item 
    // and by a food before placing food.
    if (!_snake.snake_cell(x, y) /*&& (x != _food.x && y != _food.y)*/) 
    {
      _obstacle.x = x;
      _obstacle.y = y;
      return;
    }
  }
}