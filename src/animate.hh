#ifndef ANIMATE_HH
# define ANIMATE_HH

#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/Sprite.hpp>

class Animate
{
public:
    Animate();
    Animate(sf::Sprite sprite, int width, int height,
            int start = 0, int nb_frames = 3);
    /*
    **  Move animates the character.
    **  state sets the orientation of the character = 0 : right, 1 : left.
    **  speedanim is the speed of the animation
    */
    sf::Rect<int> move(int state, int speed_anim = 10);
    /*
    **  Changes the starting point on the sprite image.
    */
    void start_set(int start);
    /*
    ** Stop stops the animation of the character.
    */
    sf::Rect<int> stop(int state, int start = -1);
private:
    sf::Sprite sprite_;
    int width_;
    int height_;
    int frame_;
    bool increment_;
    int nb_frames_;
    int start_;
    sf::Clock clock_;
};

#endif /* !ANIMATE_HH */
