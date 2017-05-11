#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>

class Drone : public Character
{
  public:
    Drone(float x, float y, int timer_wait, int timer_shoot);

    void update() override;
    void draw(sf::RenderWindow& window) override;
    void update_laser();
    void move() override;
    void shoot();
    int get_height_laser();
    void init();
  private:
    int timer_wait_;
    int timer_shoot_;
    sf::Clock clock_;
    bool shooting_;
    float x_end_;
    float y_end_;
    int height_laser_;
    sf::RectangleShape laser_;
    sf::Rect<float> rectangle_;
};
