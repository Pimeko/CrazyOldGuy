#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window.hpp>
#include <memory>
#include "content-manager.hh"
#include "manager.hh"
#include "game-manager.hh"
#include "menu-manager.hh"
#include "end-manager.hh"
#include "pause-manager.hh"
#include "switch-manager.hh"
#include "bad-end.hh"

void update()
{
  switch (Manager::gamestate_)
  {
    case Manager::MENU:
      {
        MenuManager::update();
        break;
      }
    case Manager::IN_GAME:
      {
        GameManager::update_game();
        break;
      }
    case Manager::PAUSE:
      {
        PauseManager::update();
        break;
      }
    case Manager::SWITCH:
      {
        SwitchManager::update();
        break;
      }
    case Manager::END_BAD:
      {
        EndBad::update();
        break;
      }
    case Manager::END_GOOD:
      {
        EndManager::update();
        break;
      }
  }
}

void draw(sf::RenderWindow& window)
{
  switch (Manager::gamestate_)
  {
    case Manager::MENU:
      {
        MenuManager::draw(window);
        break;
      }
    case Manager::IN_GAME:
      {
        GameManager::draw_game(window);
        break;
      }
    case Manager::PAUSE:
      {
        GameManager::draw_game(window);
        PauseManager::draw(window);
        break;
      }
    case Manager::SWITCH:
      {
        SwitchManager::draw(window);
        break;
      }
    case Manager::END_BAD:
      {
        EndBad::draw(window);
        break;
      }
    case Manager::END_GOOD:
      {
        EndManager::draw(window);
        break;
      }
  }
}

int main()
{
  GameManager::window_w_ = 1280;
  GameManager::window_h_ = 1024;

  sf::RenderWindow window(sf::VideoMode(1280, 1024), "Crazy Old Guy",
                          sf::Style::Fullscreen);
  window.setFramerateLimit(0);


  Manager::gamestate_ = Manager::MENU;
  int t;

  while (window.isOpen())
  {
    t = 0;
    sf::Clock bigClock;
    sf::Event event;
    while (window.pollEvent(event))
    {
      if (event.type == sf::Event::Closed)
        window.close();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    {
      window.close();
      break;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::N))
      Manager::change_level();
    window.clear();

    update();
    draw(window);

    window.display();

    sf::Time time = bigClock.getElapsedTime();
    t = time.asMicroseconds();

    for (; t < 2800;)
    {
      sf::Time time = bigClock.getElapsedTime();
      t = time.asMicroseconds();
    }
  }
  return 0;
}
