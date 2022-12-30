#include <iostream>
#include "controller.h"
#include "game.h"
#include "renderer.h"

int main() {
  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{640};
  constexpr std::size_t kScreenHeight{640};
  constexpr std::size_t kGridWidth{32};
  constexpr std::size_t kGridHeight{32};

  Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  Controller controller;
  Game game(kGridWidth, kGridHeight);
  game.run(controller, renderer, kMsPerFrame);
  std::cout << "Game has terminated successfully!\n";
  std::cout << "Score: " << game.get_score() << "\n";
  std::cout << "Size: " << game.get_size() << "\n";
  
  char save;
  do
  {
    std::cout << "Do you want to save the result of this game? [y/n]\n";
    std::cin >> save;
  }
  while (save != 'y' && save != 'n');

  if (save == 'y')
  {
    game.update_statistics();
  }  
  
  return 0;
}