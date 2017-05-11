#include "manager.hh"
#include "game-manager.hh"

int Manager::gamestate_ = MENU;

void Manager::change_level()
{
  if (GameManager::curr_level_ != GameManager::nb_levels_)
    Manager::gamestate_ = SWITCH;
  if (GameManager::curr_level_ == GameManager::nb_levels_)
    Manager::gamestate_ = END_GOOD;
}
