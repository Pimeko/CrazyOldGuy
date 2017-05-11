#pragma once

#include <SFML/Window.hpp>
#include <memory>
#include <vector>
#include "content-manager.hh"
#include "map.hh"
#include "hud.hh"
#include "cop.hh"
#include "drone.hh"
#include "player.hh"
#include "manager.hh"

class GameManager
{
  public:

    static Manager::GameState gamestate_;

    static std::shared_ptr<ContentManager> content_;
    static int nb_levels_;

    /* General Map attributes */
    static int window_w_;
    static int window_h_;
    static int map_width_;
    static int map_height_;
    static int array_width_;
    static int array_height_;
    static int tilesize_;
    static std::shared_ptr<Map> map_;
    static int curr_level_;
    static int x_ini_;
    static int y_ini_;
    static int x_end_;
    static int y_end_;
    static int timeout_;

    static std::shared_ptr<Player> hero_;
    static std::shared_ptr<Hud> hud_;
    static int nb_enemies_;
    static std::vector<Cop> enemies_;
    static std::vector<Drone> drones_;

    static void init_game(int level);
    static void restart_game();
    static void update_game();
    static void draw_game(sf::RenderWindow& window);
};
