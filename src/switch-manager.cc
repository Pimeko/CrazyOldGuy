#include "switch-manager.hh"
#include <SFML/Window/Keyboard.hpp>
#include "manager.hh"
#include "game-manager.hh"

void SwitchManager::update()
{
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
  {
    GameManager::curr_level_ += 1;
    Manager::gamestate_ = Manager::IN_GAME;
    GameManager::restart_game();
  }
}

void SwitchManager::draw(sf::RenderWindow& window)
{
   sf::Sprite sprite;
   sprite.setTexture(GameManager::content_->SwitchMenu);
   window.draw(sprite);
   sf::Sprite spritetext;
   spritetext.setTexture(GameManager::content_->MenuText);
   spritetext.setPosition(50, 420);
   window.draw(spritetext);
}
