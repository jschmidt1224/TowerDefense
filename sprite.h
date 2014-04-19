

#ifndef SPRITE_H
#define SPRITE_H

#include "SDL/SDL.h"
#include "Rectangle.h"

#define HIT_TOP 1
#define HIT_BOTTOM 2
#define HIT_LEFT 4
#define HIT_RIGHT 8

class Sprite
{
  public:
  MyRect position_;
  MyRect speed_;
  MyRect previous_;
  public:
  SDL_Surface* surface;
  SDL_Rect clip;

  Sprite();
  Sprite(MyRect);
  Sprite(int, int);

  char collision_check(Sprite, MyRect);
  void draw();
  void step(int);

  MyRect get_position();
  MyRect get_speed();
  MyRect get_previous();

  void set_position(MyRect);
  void set_speed(MyRect);
};


#endif
