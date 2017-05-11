#include <SFML/Window/Keyboard.hpp>

#include "pause-manager.hh"
#include "manager.hh"
#include "game-manager.hh"

void PauseManager::update()
{
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
    Manager::gamestate_ = Manager::IN_GAME;
}

void PauseManager::draw(sf::RenderWindow& window)
{
  sf::Sprite sprite;
  sprite.setTexture(GameManager::content_->Pause);
  window.draw(sprite);
}
