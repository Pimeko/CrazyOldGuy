#ifndef ENEMY_HH
# define ENEMY_HH

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>
#include <memory>
#include "character.hh"
#include "animate.hh"
#include "vision-ray.hh"

class Cop : public Character
{
public:
    Cop(float x, float y, float xf, int wait_time_);

    bool keep_update_vision();
    void update_torchlight();
    void update() override;
    void draw(sf::RenderWindow& window) override;
    void move() override;
private:
    float xb_;
    float xf_;
    int wait_time_;
    std::shared_ptr<VisionRay> vision_ray_;
    bool can_send_ray_;
    sf::ConvexShape vision_;
};

#endif /* !ENEMY_HH */
