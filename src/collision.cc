#include <SFML/Graphics/Rect.hpp>
#include <vector>
#include "game-manager.hh"
#include "collision.hh"

bool Collision::col_player_obst(sf::Rect<float>& p, std::vector<int>& array)
{
  int ts = GameManager::tilesize_;
  for (int i = 0; i < GameManager::array_height_; i++)
  {
    for (int j = 0; j < GameManager::array_width_; j++)
    {
      if (array[i * GameManager::array_width_ + j])
      {
        sf::Rect<float> curr(sf::Vector2f(j * ts, i * ts),
            sf::Vector2f(ts, ts));
        if (curr.intersects(p)) // Collision
          return true;
      }
    }
  }
  return false;
}

bool Collision::col_obst(sf::Rect<float>& r)
{
  int ts = GameManager::tilesize_;
  std::vector<int> obst = GameManager::map_->get_obstacles();
  for (int i = 0; i < GameManager::array_height_; i++)
  {
    for (int j = 0; j < GameManager::array_width_; j++)
    {
      if (obst[i * GameManager::array_width_ + j])
      {
        sf::Rect<float> curr(sf::Vector2f(j * ts, i * ts),
            sf::Vector2f(ts, ts));
        if (r.intersects(curr)) // Collision Obstacles
          return true;
      }
    }
  }
  return false;
}

bool Collision::col_hero(sf::Rect<float>& r)
{
  return !GameManager::hero_->get_invis()
         && !GameManager::hero_->get_hidden()
         && r.intersects(GameManager::hero_->get_rectangle());
}

float Collision::col_spot(sf::Rect<float>& r)
{
  int ts = GameManager::tilesize_;
  std::vector<int> spots = GameManager::map_->get_spots();
  for (int i = 0; i < GameManager::array_height_; i++)
  {
    for (int j = 0; j < GameManager::array_width_; j++)
    {
      if (spots[i * GameManager::array_width_ + j])
      {
        sf::Rect<float> curr(sf::Vector2f(j * ts, i * ts),
            sf::Vector2f(ts, ts));
        if (r.intersects(curr)) // Collision Spot
          return j* ts;
      }
    }
  }
  return -1;
}

bool Collision::player_on_end(sf::Rect<float>& r)
{
  int ts = GameManager::tilesize_;
  sf::Rect<float> curr(sf::Vector2f(GameManager::x_end_ *
  ts, GameManager::y_end_ * ts), sf::Vector2f(ts, ts));
  return r.intersects(curr);

}
