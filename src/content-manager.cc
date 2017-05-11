#include "content-manager.hh"

ContentManager::ContentManager()
{
  font_.loadFromFile("content/PressStart2P.ttf");
  map_tiles_.loadFromFile("content/tiles.png");
  playerTexture.loadFromFile("content/hero.png");
  playerHiddenTexture.loadFromFile("content/hidden.png");
  enemyTexture.loadFromFile("content/enemy.png");
  droneTexture.loadFromFile("content/drone.png");
  Menu.loadFromFile("content/Menu.png");
  End.loadFromFile("content/End.jpg");
  Pause.loadFromFile("content/Pause.png");
  MenuText.loadFromFile("content/MenuText.png");
  SwitchMenu.loadFromFile("content/SwitchMenu.png");
  GameOver.loadFromFile("content/GameOver.png");
  GoodEnd.loadFromFile("content/GoodEnd.png");
}
