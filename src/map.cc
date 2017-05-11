#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>
#include <iostream>
#include <fstream>
#include <memory>
#include <vector>

#include "game-manager.hh"
#include "map.hh"
#include "player.hh"
#include "enemy.hh"
# define NB_T 5

Map::Map(std::string filename, sf::Texture texture)
  : filename_(filename)
    , texture_(texture)
{
  sf::Vector2<unsigned int> size = texture_.getSize();
  w_map_ = size.x;
  h_map_ = size.y;
}

Map::~Map()
{}

void Map::set_ground(std::ifstream& file)
{
  std::string curr;

  auto curr_i = 0;
  auto curr_j = 0;
  while (curr_i != h_array_ && file >> curr)
  {
    ground_[curr_i * w_array_ + curr_j] = atoi(curr.c_str());

    curr_j = (curr_j + 1) % w_array_;
    if (curr_j == 0)
      curr_i++;
  }
}

void Map::set_obstacles(std::ifstream& file)
{
  std::string curr;

  int curr_i = 0;
  int curr_j = 0;
  while (curr_i != h_array_ && file >> curr)
  {
    obstacles_[curr_i * w_array_ + curr_j] = atoi(curr.c_str());

    curr_j = (curr_j + 1) % w_array_;
    if (curr_j == 0)
      curr_i++;
  }
}

void Map::set_enemies(std::ifstream& file)
{
  std::string curr;
  file >> curr;
  GameManager::nb_enemies_ = atoi(curr.c_str());

  for (int i = 0; i < GameManager::nb_enemies_; i++)
  {
    file >> curr;
    bool cop = atoi(curr.c_str()) == 1;

    file >> curr;
    float x = atof(curr.c_str());
    file >> curr;
    float y = atof(curr.c_str());

    if (cop)
    {
      file >> curr;
      float z = atof(curr.c_str());
      file >> curr;
      int wait = atoi(curr.c_str());

      GameManager::enemies_.push_back(Cop(x, y, z, wait));
    }
    else // Drone
    {
      file >> curr;
      int timer_wait = atoi(curr.c_str());
      file >> curr;
      int timer_shoot = atoi(curr.c_str());

      GameManager::drones_.push_back(Drone(x, y, timer_wait, timer_shoot));
    }
  }
}

void Map::set_spots(std::ifstream& file)
{
  std::string curr;

  int curr_i = 0;
  int curr_j = 0;
  while (curr_i != h_array_ && file >> curr)
  {
    spots_[curr_i * w_array_ + curr_j] = atoi(curr.c_str());

    curr_j = (curr_j + 1) % w_array_;
    if (curr_j == 0)
      curr_i++;
  }
}

int Map::init_map()
{
  std::ifstream file(filename_, std::ios::in);
  if (!file)
  {
    std::cerr << "Error opening the file " << filename_ << "\n";
    return 1;
  }

  std::string curr;
  // Size map
  file >> curr;
  w_array_ = atoi(curr.c_str());
  GameManager::array_width_ = w_array_;
  file >> curr;
  h_array_ = atoi(curr.c_str());
  GameManager::array_height_ = h_array_;
  file >> curr;
  GameManager::timeout_ = atoi(curr.c_str());

  ts_ = w_map_ / NB_T;
  GameManager::tilesize_ = ts_;
  GameManager::map_width_ = w_map_;
  GameManager::map_height_ = h_map_;

  ground_.resize(w_array_ * h_array_);
  obstacles_.resize(w_array_ * h_array_);
  spots_.resize(w_array_ * h_array_);

  // Pos init
  file >> curr;
  GameManager::x_ini_ = atoi(curr.c_str());
  file >> curr;
  GameManager::y_ini_ = atoi(curr.c_str());

  // Pos end
  file >> curr;
  GameManager::x_end_ = atoi(curr.c_str());
  file >> curr;
  GameManager::y_end_ = atoi(curr.c_str());

  set_enemies(file);
  set_ground(file);
  set_obstacles(file);
  set_spots(file);
  return 0;
}

std::vector<int>& Map::get_ground()
{
  return ground_;
}

std::vector<int>& Map::get_obstacles()
{
  return obstacles_;
}

std::vector<int>& Map::get_spots()
{
  return spots_;
}

void Map::draw_ground(sf::RenderWindow& window)
{
  for (int i = 0; i < h_array_; i++)
  {
    for (int j = 0; j < w_array_; j++)
    {
      sf::Sprite sprite;
      sprite.setTexture(texture_);
      int val = ground_[i * w_array_ + j];
      int i_ = val % NB_T;
      int j_ = val / NB_T;
      sprite.setTextureRect(sf::IntRect(i_ * ts_, j_ * ts_, ts_, ts_));
      sprite.setPosition(j * ts_, i * ts_);

      window.draw(sprite);
    }
  }
}

void Map::draw_obstacles(sf::RenderWindow& window)
{
  for (int i = 0; i < h_array_; i++)
  {
    for (int j = 0; j < w_array_; j++)
    {
      sf::Sprite sprite;
      sprite.setTexture(texture_);
      int val = obstacles_[i * w_array_ + j];
      if (val == 0)
        continue;
      int i_ = val % NB_T;
      int j_ = val / NB_T;
      sprite.setTextureRect(sf::IntRect(i_ * ts_, j_ * ts_, ts_, ts_));
      sprite.setPosition(j * ts_, i * ts_);

      window.draw(sprite);
    }
  }
}

void Map::draw_spots(sf::RenderWindow& window)
{
  for (int i = 0; i < h_array_; i++)
  {
    for (int j = 0; j < w_array_; j++)
    {
      sf::Sprite sprite;
      sprite.setTexture(texture_);
      int val = spots_[i * w_array_ + j];
      if (val == 0)
        continue;
      int i_ = val % NB_T;
      int j_ = val / NB_T;
      sprite.setTextureRect(sf::IntRect(i_ * ts_, j_ * ts_, ts_, ts_));
      sprite.setPosition(j * ts_, i * ts_);

      window.draw(sprite);
    }
  }
}

void Map::draw(sf::RenderWindow& window)
{
  draw_ground(window);
  draw_spots(window);
  draw_obstacles(window);
}
