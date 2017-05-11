#pragma once
#include <SFML/Graphics.hpp>


class PauseManager
{
public:
  static void update();
  static void draw(sf::RenderWindow& window);

  static int timer;
};
