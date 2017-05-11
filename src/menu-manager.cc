#include <SFML/Window/Keyboard.hpp>
#include "menu-manager.hh"
#include "game-manager.hh"
#include "content-manager.hh"

int MenuManager::timer_text = 0;
bool MenuManager::is_drawable = false;

void MenuManager::update()
{
  timer_text++;
  if (timer_text == 350)
  {
    is_drawable = true;
  }
  if (timer_text == 700)
  {
    is_drawable = false;
    timer_text = 0;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
  {
    GameManager::init_game(1);
    Manager::gamestate_ = Manager::IN_GAME;
  }
}

void MenuManager::draw(sf::RenderWindow& window)
{
  sf::Sprite sprite;
  sprite.setTexture(GameManager::content_->Menu);
  window.draw(sprite);
  if (is_drawable)
  {
    sf::Sprite sprite_text;
    sprite_text.setTexture(GameManager::content_->MenuText);
    sprite_text.setPosition(75, 750);
    window.draw(sprite_text);
  }
}
