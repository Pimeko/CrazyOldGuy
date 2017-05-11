#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <iostream>

#include "game-manager.hh"
#include "player.hh"
#include "collision.hh"
#include "manager.hh"

# define SPEED 0.5

Player::Player(float x, float y)
  : Character(x, y)
{
  width_ = 32;
  height_ = 32;
  sprite_.setTexture(GameManager::content_->playerTexture);
  sprite_.setPosition(x, y);
  animation_ = Animate(sprite_, 32, 32, 0);
  jump_acceleration_ = 90;
  state_pos_ = FALLING;
  invis_ = 1500;
  is_invis_ = false;
  hidden_ = false;
  hasPressedE_ = false;
  haspressedR_ = false;
  hasPressedQ_ = false;
  skin_ = 0;
}
void Player::init()
{
  width_ = 32;
  height_ = 32;
  sprite_.setTexture(GameManager::content_->playerTexture);

  animation_ = Animate(sprite_, 32, 32, 0);
  jump_acceleration_ = 90;
  state_pos_ = FALLING;
  invis_ = 1500;
  is_invis_ = false;
}
void Player::move()
{

  if (!hidden_)
  {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
      sf::Rect<float> hypo(sf::Vector2f(x_ - SPEED, y_),
          sf::Vector2f(width_, height_));
      if (!Collision::col_player_obst(hypo, GameManager::map_->get_obstacles()))
      {
        x_ -= SPEED;
        sprite_.move(-SPEED, 0);
        state_anim_ = 1;
      }
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
      sf::Rect<float> hypo(sf::Vector2f(x_ + SPEED, y_),
          sf::Vector2f(width_, height_));
      if (!Collision::col_player_obst(hypo, GameManager::map_->get_obstacles()))
      {
        x_ += SPEED;
        sprite_.move(SPEED, 0);
        state_anim_ = 2;
      }
    }
    else
      state_anim_ = 0;
  }
}


bool Player::apply_gravity()
{
  if (state_pos_ != JUMPING)
  {
    bool falling = Character::apply_gravity();
    if (!falling)
      state_pos_ = STABLE;
    return falling;
  }
  return true;
}

void Player::jump()
{
  if (!hidden_)
  {
    if (state_pos_ == JUMPING)
    {
      float speed = 0.01 * jump_acceleration_;
      sf::Rect<float> hypo(sf::Vector2f(x_, y_ - speed),
          sf::Vector2f(width_, height_));

      if (jump_acceleration_ <= 0)
        state_pos_ = FALLING;
      else if (!Collision::col_player_obst(hypo,
            GameManager::map_->get_obstacles()))
      {
        y_ -= speed;
        sprite_.move(0, -speed);

        jump_acceleration_ -= 0.01;
      }
      else
        state_pos_ = FALLING;
    }
    else if (state_pos_ == STABLE)
    {
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
      {
        state_pos_ = JUMPING;
        jump_acceleration_ = 90;
      }
    }
  }
}

void Player::hide()
{
  sf::Rect<float> rect_(sf::Vector2f(x_, y_),
        sf::Vector2f(width_, height_));
  float x = 0;
  if (hidden_)
  {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
      hasPressedE_ = true;
    if (!sf::Keyboard::isKeyPressed(sf::Keyboard::E) && hasPressedE_)
    {
      GameManager::hud_->disable_text_hide();
      sprite_.setTexture(GameManager::content_->playerTexture);
      hidden_ = false;
      hasPressedE_ = false;
    }
  }
  else if ((x = Collision::col_spot(rect_)) != -1)
  {
    GameManager::hud_->toggle_text_hide(true);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
      hasPressedE_ = true;
    if (!sf::Keyboard::isKeyPressed(sf::Keyboard::E) && hasPressedE_)
    {
      GameManager::hud_->toggle_text_hide(false);
      x_ = x;
      sprite_.setTexture(GameManager::content_->playerHiddenTexture);
      sprite_.setPosition(x_, y_);
      hidden_ = true;
      hasPressedE_ = false;
    }
  }
  else
    GameManager::hud_->disable_text_hide();
}

void Player::update()
{
  sf::Rect<float> hypo(sf::Vector2f(x_, y_),
        sf::Vector2f(width_, height_));
  Character::update();
  if (Collision::player_on_end(hypo))
    Manager::change_level();
  move();
  apply_gravity();
  jump();
  hide();
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
    haspressedR_ = true;

 if (!hidden_)
 {
   if (is_invis_)
     invis_--;
   if (haspressedR_ && !sf::Keyboard::isKeyPressed(sf::Keyboard::R))
   {
     is_invis_ = !is_invis_;
     haspressedR_ = false;
     if (is_invis_)
       sprite_.setColor(sf::Color(50, 200, 255, 100));
     else
       sprite_.setColor(sf::Color(255 , 255, 255));
   }

   if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
   {
     if (!hasPressedQ_)
     {
       hasPressedQ_ = true;
       if (skin_ == 7)
         skin_ = 0;
       else
         skin_++;
       animation_.start_set((skin_ / 2) * 3);
     }
   }
   else
     hasPressedQ_ = false;


   if (state_anim_)
     sprite_.setTextureRect(animation_.move(state_anim_ + 4 * (skin_ % 2)));
   else
     sprite_.setTextureRect(animation_.stop(state_anim_ + 4 * (skin_ % 2)));

   if (invis_ < 0)
   {
     is_invis_ = false;
     sprite_.setColor(sf::Color(255 , 255, 255));
   }
 }
}

int Player::get_invis_loss()
{
  return 1500 - invis_;
}

bool Player::get_invis()
{
  return is_invis_;
}

bool Player::get_hidden()
{
  return hidden_;
}

void Player::draw(sf::RenderWindow& window)
{
  window.draw(sprite_);
}
