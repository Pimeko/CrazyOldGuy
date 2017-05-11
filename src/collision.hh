#pragma once
#include <SFML/Graphics/Rect.hpp>
#include <vector>
#include "player.hh"

class Collision
{
public:
  static bool col_player_obst(sf::Rect<float>& p, std::vector<int>& array);
  static bool col_obst(sf::Rect<float>& r);
  static bool col_hero(sf::Rect<float>& r);
  static float col_spot(sf::Rect<float>& r);
  static bool player_on_end(sf::Rect<float>& r);
};
