#pragma once
#include <string>
#include <memory>
#include <SFML/Graphics/RenderWindow.hpp>
#include <iostream>

class Map
{
  public:
    Map(std::string filename, sf::Texture texture);
    ~Map();
    int init_map();
    std::vector<int>& get_ground();
    std::vector<int>& get_obstacles();
    std::vector<int>& get_spots();
    void draw(sf::RenderWindow& window);
  private:
    void set_ground(std::ifstream& f);
    void set_obstacles(std::ifstream& f);
    void set_enemies(std::ifstream& f);
    void set_spots(std::ifstream& f);
    void draw_ground(sf::RenderWindow& window);
    void draw_obstacles(sf::RenderWindow& window);
    void draw_spots(sf::RenderWindow& window);
    std::string filename_;
    sf::Texture texture_;
    std::vector<int> ground_;
    std::vector<int> obstacles_;
    std::vector<int> spots_;
    int w_array_;
    int h_array_;
    int w_map_;
    int h_map_;
    int ts_;
};
