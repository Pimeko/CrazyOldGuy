#ifndef HUD_HH
# define HUD_HH

#include <SFML/Window.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

class Hud
{
public:
    Hud();
    void clear_hud();
    void update(int loss);
    void draw(sf::RenderWindow& window);
    void toggle_text_hide(bool enter);
    void disable_text_hide();
private:
    sf::Clock clock_;
    sf::Text text_time_;
    sf::Text text_hide_;
    sf::Font font_;
    int minutes_;
    int power_max_;
    sf::RectangleShape power_bar_;
    bool print_text_hide_;
};

#endif /* !HUD_HH */
