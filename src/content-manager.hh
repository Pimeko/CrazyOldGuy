#pragma once
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>

class ContentManager
{
public:
  ContentManager();
  sf::Font font_;
  sf::Texture map_tiles_;
  sf::Texture playerTexture;
  sf::Texture playerHiddenTexture;
  sf::Texture enemyTexture;
  sf::Texture droneTexture;
  sf::Texture Menu;
  sf::Texture End;
  sf::Texture Pause;
  sf::Texture MenuText;
  sf::Texture SwitchMenu;
  sf::Texture GameOver;
  sf::Texture GoodEnd;
};
