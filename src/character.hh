#ifndef CHARACTER_HH
# define CHARACTER_HH

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Clock.hpp>
#include "animate.hh"

class Character
{
  public:
    Character(float x, float y);

    virtual void move() = 0;
    virtual void update();

    /*
    ** Return true if falling, false otherwise
    */
    virtual bool apply_gravity();

    virtual void draw(sf::RenderWindow& window) = 0;
    sf::Rect<float>& get_rectangle();

  protected:
    float x_;
    float y_;
    float width_;
    float height_;
    sf::Rect<float> rectangle_;
    sf::Sprite sprite_;
    Animate animation_;
    int state_anim_;
    sf::Clock clock_;
    float speed_gravity_;
};


#endif /* !CHARACTER_HH */
