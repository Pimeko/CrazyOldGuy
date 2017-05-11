#include <SFML/Window.hpp>
#include "game-manager.hh"

std::shared_ptr<ContentManager> GameManager::content_ =
std::make_shared<ContentManager>();
int GameManager::nb_levels_ = 3;

/* General Map attributes */
int GameManager::window_w_ = 0;
int GameManager::window_h_ = 0;
int GameManager::map_width_ = 0;
int GameManager::map_height_ = 0;
int GameManager::array_width_ = 0;
int GameManager::array_height_ = 0;
int GameManager::tilesize_ = 0;
int GameManager::curr_level_ = 0;
int GameManager::x_ini_ = 0;
int GameManager::y_ini_ = 0;
int GameManager::x_end_ = 0;
int GameManager::y_end_ = 0;
int GameManager::timeout_ = 0;
std::shared_ptr<Map> GameManager::map_ = nullptr;


std::shared_ptr<Player> GameManager::hero_ = nullptr;
std::shared_ptr<Hud> GameManager::hud_ = nullptr;
int GameManager::nb_enemies_ = 0;
std::vector<Cop> GameManager::enemies_ = std::vector<Cop>();
std::vector<Drone> GameManager::drones_ = std::vector<Drone>();

void GameManager::init_game(int level)
{
  curr_level_ = level;
  std::string level_name = "levels/level";
  level_name.append(std::to_string(level).append(".map"));
  map_ = std::make_shared<Map>(level_name, content_->map_tiles_);
  map_->init_map();
  hero_ = std::make_shared<Player>(x_ini_, y_ini_);
  hero_->init();
  hud_ = std::make_shared<Hud>();
  for (auto& drone: drones_)
    drone.init();
}

void GameManager::restart_game()
{
  hud_->clear_hud();
  enemies_.clear();
  drones_.clear();
  if (curr_level_ > nb_levels_)
    curr_level_ = 1;
  init_game(GameManager::curr_level_);
}

void GameManager::update_game()
{
  for (auto& cop: enemies_)
    cop.update();
  for (auto& drone: drones_)
    drone.update();
  hero_->update();
  hud_->update(hero_->get_invis_loss());
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
    Manager::gamestate_ = Manager::PAUSE;
}

void GameManager::draw_game(sf::RenderWindow& window)
{
  map_->draw(window);
  hud_->draw(window);
  hero_->draw(window);
  for (auto& enemy: enemies_)
    enemy.draw(window);
  for (auto& drone: drones_)
    drone.draw(window);

}
