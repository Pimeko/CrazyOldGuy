#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Clock.hpp>
#include <iostream>
#include "animate.hh"

Animate::Animate()
{}

Animate::Animate(sf::Sprite sprite, int width, int height,
                 int start, int nb_frames)
    : sprite_(sprite)
    , width_(width)
    , height_(height)
    , frame_(0)
    , increment_(true)
    , nb_frames_(nb_frames)
    , start_(start)
{}

sf::Rect<int> Animate::move(int state, int speed_anim)
{
  if (frame_ >= nb_frames_)
  {
    frame_ = nb_frames_ - 1;
    increment_ = false;
  }
  if (frame_ < 0)
  {
    frame_ = 0;
    increment_ = true;
  }

  speed_anim *= 10;
  sf::Time t = clock_.getElapsedTime();
  int time = t.asMilliseconds();

  int left = (start_ + frame_) * width_;
  int top = state * height_;

  sf::Rect<int> rect(left, top, width_, height_);

  if (increment_ && time > speed_anim)
  {
    clock_.restart();
    frame_++;
  }
  else if (!increment_ && time > speed_anim)
  {
    clock_.restart();
    frame_--;
  }

  return rect;
}

void Animate::start_set(int start)
{
  start_ = start;
}

sf::Rect<int> Animate::stop(int state, int start)
{
  if (start == -1)
    start = start_;

  clock_.restart();
  increment_ = true;
  frame_ = 0;
  int left = (start_ + 1) * width_;
  int top = state * height_;

  sf::Rect<int> rect(left, top, width_, height_);

  return rect;
}
