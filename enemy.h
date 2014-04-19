
#ifndef ENEMY_H
#define ENEMY_H
#include "sprite.h"
#include "path.h"
#include <list.h>
#include "bullet.h"
#include "gas.h"

#define PHYS 1
#define ELEC 2
#define CHEM 4
#define FIRE 8

class Enemy : public Sprite
{
public:
  char resists_;
  float health_;
  float maxHealth_;
  int attackSpeed_;
  int damage_;
  int maxSpeed_;
  int stopTimer;
public:
  Enemy() : Sprite()
  {
    maxHealth_ = 0;
    health_ = 0;
    attackSpeed_ = 0;
    resists_ = 0;
    damage_ = 0;
    speed_.y = -80;
    maxSpeed_ = 80;
    position_.w = 16;
    position_.h = 16;
  }
  Enemy(MyRect r) : Sprite(r)
  {
    maxHealth_ = 0;
    health_ = 0;
    attackSpeed_ = 0;
    resists_ = 0;
    damage_ = 0;
    speed_.y = -80;
    maxSpeed_ = 80;
    position_.w = 16;
    position_.h = 16;
  }
  Enemy(MyRect r, int mh, int as, int d, char re) : Sprite(r)
  {
    maxHealth_ = mh;
    health_ = mh;
    attackSpeed_ = as;
    resists_ = re;
    damage_ = d;
    speed_.y = -80;
    maxSpeed_ = 80;
    position_.w = 16;
    position_.h = 16;
  }
  Enemy(int x, int y, int mh, int as, int d, char re) : Sprite(x, y)
  {
    maxHealth_ = mh;
    health_ = mh;
    attackSpeed_ = as;
    resists_ = re;
    damage_ = d;
    speed_.y = -80;
    maxSpeed_ = 80;
    position_.w = 16;
    position_.h = 16;
  }

  void step(int d, list<Path>& P, list<Bullet>& B, list<Gas>& G);
  void hit(float, char);
  void draw();

};

#endif

