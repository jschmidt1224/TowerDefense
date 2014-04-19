
#ifndef BULLET_H
#define BULLET_H

#include "sprite.h"


class Bullet : public Sprite
{
public:
  int damage;
  bool explode;
  Sprite* target;
  float maxSpeed;
  Bullet(int, int, int, bool, float, Sprite*);
  void step(int);
};

#endif


