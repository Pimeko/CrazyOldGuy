#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>
#include <memory>
#include "cop.hh"
#include "vision-ray.hh"
#include "game-manager.hh"

# define SPEED 0.1

enum STATE_ANIM
{
  LEFT = 0,
  RIGHT = 1,
  STAND_LEFT = 2,
  STAND_RIGHT = 3
};

Cop::Cop(float x, float y, float xf, int wait_time)
  : Character(x, y)
  , wait_time_(wait_time)
  , can_send_ray_(true)
{
  state_anim_ = 1;
  sprite_.setTexture(GameManager::content_->enemyTexture);
  sprite_.setPosition(x, y);
  width_ = 32;
  height_ = 32;

  animation_ = Animate(sprite_, width_, height_, 3);
  if (xf < x)
  {
    xb_ = xf;
    xf_ = x;
  }
  else
  {
    xb_ = x;
    xf_ = xf;
  }
}

bool Cop::keep_update_vision()
{
  if (can_send_ray_)
  {
    vision_ray_ = std::make_shared<VisionRay>(x_ + width_ / 2,
                                              y_ + height_ / 2,
                                              state_anim_ % 2, 100);
    can_send_ray_ = false;
    return true;
  }
  else
  {
    vision_ray_->update();
    if (!vision_ray_->is_alive())
    {
      if (vision_ray_->found_hero())
      {
        Manager::gamestate_ = Manager::END_BAD;
        return false;
      }
      can_send_ray_ = true;
    }
    return true;
  }
}

void Cop::update_torchlight()
{
  vision_.setFillColor(sf::Color(255, 255, 100, 50));
  vision_.setOutlineColor(sf::Color(255, 255, 0));
  vision_.setPointCount(3);

  if (state_anim_ == RIGHT || state_anim_ == STAND_RIGHT)
  {
    vision_.setPoint(0, sf::Vector2f(x_ + width_ / 2, y_ + (height_ * 7) / 9));
    vision_.setPoint(1, sf::Vector2f(x_ + width_ / 2 + 100, y_));
    vision_.setPoint(2, sf::Vector2f(x_ + width_ / 2 + 100, y_ + height_));
  }
  else
  {
    vision_.setPoint(0, sf::Vector2f(x_ + width_ / 2, y_ + (height_ * 7) / 9));
    vision_.setPoint(1, sf::Vector2f(x_ + width_ / 2 - 100, y_));
    vision_.setPoint(2, sf::Vector2f(x_ + width_ / 2 - 100, y_ + height_));
  }
}

void Cop::update()
{
  Character::update();
  apply_gravity();
  keep_update_vision();
  move();
  update_torchlight();
}

void Cop::draw(sf::RenderWindow& window)
{

  window.draw(vision_);
  window.draw(sprite_);
}

void Cop::move()
{
  sf::Time t = clock_.getElapsedTime();
  int time = t.asMilliseconds();

  if (x_ > xf_ && state_anim_ < STAND_LEFT && time > 100)
  {
    state_anim_ = STAND_RIGHT;
    clock_.restart();
    time = 0;
  }
  if (x_ < xb_ && state_anim_ < STAND_LEFT && time > 100)
  {
    state_anim_ = STAND_LEFT;
    clock_.restart();
    time = 0;
  }

  if (state_anim_ > RIGHT)
  {
    if (time >= wait_time_ && state_anim_ == STAND_LEFT)
      state_anim_ = RIGHT;
    else if (time >= wait_time_)
      state_anim_ = LEFT;
  }

  if (state_anim_ == RIGHT)
  {
    x_ += SPEED;
    sprite_.move(SPEED, 0);
  }
  else if (!state_anim_)
  {
    x_ -= SPEED;
    sprite_.move(-SPEED, 0);
  }

  update_torchlight();

  if (state_anim_ == STAND_LEFT)
    sprite_.setTextureRect(animation_.stop(state_anim_ + 3));
  else if (state_anim_ == STAND_RIGHT)
    sprite_.setTextureRect(animation_.stop(state_anim_ + 3));
  else if (state_anim_ == RIGHT)
    sprite_.setTextureRect(animation_.move(state_anim_ + 5));
  else
    sprite_.setTextureRect(animation_.move(state_anim_ + 5));
}
