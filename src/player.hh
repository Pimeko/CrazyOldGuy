#pragma once

#include "character.hh"
#include "animate.hh"

class Player : public Character
{
public:
  Player(float x, float y);
  enum StatePos
  {
    FALLING,
    JUMPING,
    STABLE
  };

  void init();
  bool apply_gravity() override;
  void move() override;
  void update() override;
  void jump();
  void hide();
  void draw(sf::RenderWindow& window) override;
  int get_width();
  int get_height();
  int get_invis_loss();
  bool get_invis();
  bool get_hidden();
  bool check_player_on_end();
private:
  sf::Rect<float> rectangle_;
  float coef_jump_;
  StatePos state_pos_;
  int jump_acceleration_;
  int invis_;
  int skin_;
  bool is_invis_;
  bool hasPressedQ_;
  bool haspressedR_;
  bool hasPressedE_;
  bool hidden_;
};
