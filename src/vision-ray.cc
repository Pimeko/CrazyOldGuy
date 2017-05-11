#include <SFML/Graphics.hpp>
#include "vision-ray.hh"
#include "collision.hh"
#include "game-manager.hh"

VisionRay::VisionRay(float x, float y, int dir, float dist)
: x_(x)
, y_(y)
, dir_(dir)
, dist_(dist)
, dist_done_(0)
, speed_(1.5)
, found_hero_(false)
, alive_(true)
{
  rectangle_ = sf::Rect<float>(x_, y_, 5, 5);
}

void VisionRay::update()
{
  if (alive_)
  {
    rectangle_ = sf::Rect<float>(x_, y_, 5, 5);
    if (Collision::col_obst(rectangle_) || dist_done_ >= dist_)
      destroy(false);
    else if (GameManager::hero_ && Collision::col_hero(rectangle_))
      destroy(true);
    else
    {
      if (dir_ == 0) // right
        x_ -= speed_;
      else if (dir_ == 1) // left
        x_ += speed_;
      else if (dir_ == 2) // bot
        y_ += speed_;
      else // top
        y_ -= speed_;
      dist_done_ += speed_;
    }
  }
}

void VisionRay::destroy(bool found_hero)
{
  found_hero_ = found_hero;
  alive_ = false;
}

bool VisionRay::found_hero()
{
  return found_hero_;
}

bool VisionRay::is_alive()
{
  return alive_;
}

sf::Vector2f VisionRay::get_dead_spot()
{
  return sf::Vector2f(x_, y_);
}
