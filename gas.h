
#ifndef GAS_H
#define GAS_H

#include "sprite.h"

class Gas : public Sprite
{
public:
  float damage;
  Gas(int x, int y) : Sprite(x, y){damage = .1;};
  void draw(){Sprite::draw();position_.w = 255;position_.h = 255;};
  void levelup(int l){damage=.1*l*l;};
};

#endif
