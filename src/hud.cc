#include <SFML/System/Clock.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>
#include <string>
#include <iostream>
#include "hud.hh"
#include "game-manager.hh"
#include "manager.hh"

Hud::Hud()
  : minutes_(0)
  , power_max_(150)
{
  text_time_.setFont(GameManager::content_->font_);
  text_time_.setColor(sf::Color(250, 250, 250));
  text_time_.setPosition(50, 10);
  text_time_.setCharacterSize(16);

  text_hide_.setFont(GameManager::content_->font_);
  text_hide_.setColor(sf::Color(255, 255, 255));
  text_hide_.setCharacterSize(16);
  std::string s("PRESS E TO HIDE");
  text_hide_.setString(s);
  int width =  s.size() * text_hide_.getCharacterSize();
  text_hide_.setPosition(GameManager::window_w_ / 2 - width / 2,
      GameManager::window_h_ - 50);
  print_text_hide_ = false;

  power_bar_.setFillColor(sf::Color(175, 230, 230));
  power_bar_.setOutlineThickness(2);
  power_bar_.setOutlineColor(sf::Color(32, 178, 170));
  power_bar_.setPosition(1000, 10);
}

void Hud::clear_hud()
{
  minutes_ = 0;
  clock_.restart();
}

void Hud::toggle_text_hide(bool enter)
{
  if (enter)
    text_hide_.setString("PRESS E TO HIDE");
  else
    text_hide_.setString("PRESS E TO LEAVE");

  print_text_hide_ = true;
}

void Hud::disable_text_hide()
{
  print_text_hide_ = false;
}

void Hud::update(int loss)
{
  sf::Time t = clock_.getElapsedTime();
  int time = GameManager::timeout_ - t.asMilliseconds() / 1000;
  minutes_ = time / 60;
  if (time < 0)
  {
    time = 0;
    Manager::gamestate_ = Manager::END_BAD;
  }

  if (time % 60 < 10)
    text_time_.setString(std::to_string(minutes_)
                         + ":0" + std::to_string(time % 60));
  else
    text_time_.setString(std::to_string(minutes_) + ":"
                         + std::to_string(time % 60));

  power_bar_.setSize(sf::Vector2f(power_max_ - loss / 10, 20));
}

void Hud::draw(sf::RenderWindow& window)
{
  window.draw(text_time_);
  window.draw(power_bar_);
  if (print_text_hide_)
    window.draw(text_hide_);
}
