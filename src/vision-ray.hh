#pragma once
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Window.hpp>
#include <SFML/System/Vector2.hpp>

class VisionRay
{
public:
  VisionRay(float x, float y, int dir, float dist);
  void update();
  sf::Rect<float>& get_rectangle() const;
  bool found_hero();
  bool is_alive();
  sf::Vector2f get_dead_spot();
private:
  void destroy(bool found_hero);
  float x_;
  float y_;
  int dir_;
  float dist_;
  float dist_done_;
  float speed_;
  sf::Rect<float> rectangle_;
  bool found_hero_;
  bool alive_;
};
