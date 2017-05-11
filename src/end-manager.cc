#include "end-manager.hh"
#include <SFML/Window/Keyboard.hpp>
#include "manager.hh"
#include "game-manager.hh"
void EndManager::update()
{
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
  {
    GameManager::curr_level_ += 1;
    GameManager::restart_game();
    Manager::gamestate_ = Manager::IN_GAME;
  }
}

void EndManager::draw(sf::RenderWindow& window)
{
  sf::Sprite sprite;
  sprite.setTexture(GameManager::content_->SwitchMenu);
  window.draw(sprite);
  sf::Sprite spritetext;
  spritetext.setTexture(GameManager::content_->GoodEnd);
  spritetext.setPosition(435, 500);
  window.draw(spritetext);
}
