#pragma once

#include "manager.hh"
#include "SFML/Graphics.hpp"


class MenuManager
{
public:

  static void update();
  static void draw(sf::RenderWindow& window);

  static int timer_text;
  static bool is_drawable;
};
