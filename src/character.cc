#include <SFML/Graphics/Rect.hpp>
#include "character.hh"
#include "collision.hh"
#include "game-manager.hh"
#include "animate.hh"

Character::Character(float x, float y)
  : x_(x)
    , y_(y)
    , state_anim_(0)
{
  speed_gravity_ = 0;
}

void Character::update()
{
  rectangle_ = sf::Rect<float>(sf::Vector2f(x_, y_),
      sf::Vector2f(width_, height_));
}

bool Character::apply_gravity()
{
  float speed = 0.5 + 1 * speed_gravity_;
  sf::Rect<float> hypo(sf::Vector2f(x_, y_ + speed),
      sf::Vector2f(width_, height_));
  if (!Collision::col_player_obst(hypo, GameManager::map_->get_obstacles()))
  {
    y_ += speed;
    sprite_.move(0, speed);
    speed_gravity_ += 0.018;
    return true;
  }
  speed_gravity_ = 0;
  return false;
}

sf::Rect<float>& Character::get_rectangle()
{
  return rectangle_;
}
