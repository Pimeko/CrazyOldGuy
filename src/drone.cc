#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>
#include "game-manager.hh"
#include "character.hh"
#include "drone.hh"
#include "collision.hh"
#include "animate.hh"
#include "vision-ray.hh"

Drone::Drone(float x, float y, int timer_wait, int timer_shoot)
  : Character(x, y)
  , timer_wait_(timer_wait)
  , timer_shoot_(timer_shoot)
  , shooting_(false)
{
  width_ = 41;
  height_ = 46;
  sprite_.setTexture(GameManager::content_->droneTexture);
  sprite_.setPosition(x, y);
}

void Drone::init()
{
  height_laser_ = get_height_laser();
  laser_ = sf::RectangleShape(sf::Vector2f(2, height_laser_));
  int x = x_;
  int y = y_;
  laser_.setFillColor(sf::Color(x % 255, y % 255, (x + y) % 255));
  laser_.setPosition(x_ + width_ / 2 - 10, y_ + height_);
  rectangle_ = sf::Rect<float>(x_ + width_ / 2 - 10, y_ + height_,
      2, height_laser_);
}

int Drone::get_height_laser()
{
  auto ray = std::make_shared<VisionRay>(x_ - width_ / 2, y_ + height_, 2,
      GameManager::map_height_);
  while (ray->is_alive())
    ray->update();
  sf::Vector2f obst = ray->get_dead_spot();
  return obst.y - (y_ + height_);
}

void Drone::update_laser()
{
  sf::Time t = clock_.getElapsedTime();
  int time = t.asMilliseconds();

  if (shooting_)
  {
    if (time < timer_shoot_) // Shoot
      shoot();
    else
    {
      clock_.restart();
      shooting_ = false;
    }
  }
  else
  {
    if (time >= timer_wait_)
    {
      shooting_ = true;
      clock_.restart();
    }
  }
}

void Drone::shoot()
{
  animation_.stop(0, 3);
  if (Collision::col_hero(rectangle_))
    Manager::gamestate_ = Manager::END_BAD;
}

void Drone::update()
{
  Character::update();

  update_laser();
  sprite_.setTextureRect(sf::Rect<int>(3 * width_, 0, width_, height_));
}

void Drone::draw(sf::RenderWindow& window)
{
  window.draw(sprite_);
  if (shooting_)
    window.draw(laser_);
}

void Drone::move()
{}
