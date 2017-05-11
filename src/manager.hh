#pragma once

class Manager
{
public:
  enum GameState
  {
    MENU,
    MENU_IN_GAME,
    IN_GAME,
    SWITCH,
    PAUSE,
    END_BAD,
    END_GOOD
  };

  static int gamestate_;
  static void change_level();
};
