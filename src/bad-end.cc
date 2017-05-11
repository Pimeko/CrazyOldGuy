#include "bad-end.hh"
#include "game-manager.hh"
#include <SFML/Window/Keyboard.hpp>

void EndBad::update()
{
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
  {
    GameManager::restart_game();
    Manager::gamestate_ = Manager::IN_GAME;
  }
}

void EndBad::draw(sf::RenderWindow& window)
{
  sf::Sprite sprite;
  sprite.setTexture(GameManager::content_->SwitchMenu);
  sf::Sprite spritetext;
  spritetext.setTexture(GameManager::content_->GameOver);
  spritetext.setPosition(410, 1024 / 2 + 20);
  window.draw(sprite);
  window.draw(spritetext);
}
