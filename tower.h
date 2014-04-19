
#ifndef TOWER_H
#define TOWER_H

#include "sprite.h"
#include "enemy.h"
#include "SDL\SDL_ttf.h"
#include "gas.h"

#define ME 1
#define EE 2
#define ChE 4
#define KE 8

extern SDL_Surface* load_image(std::string, bool, int, int, int);


class Tower : public Sprite
{
public:
  char type_;
  float angle_;
  bool isSet;
  float range_;
  bool canShoot;
  int reload;
  int shootLength;
  int damage;
  int damageD;
  int level;
  bool isShooting;
  int shootTimer;
  SDL_Surface* yellow;
  SDL_Surface* gas;
  TTF_Font* arial32;
  Enemy* target;
  list<Gas>::iterator gasIt;
public:

  Tower(MyRect r, char type) : Sprite(r)
  {
    type_ = type;
    isSet = false;
    shootLength = 1000;
    shootTimer = 0;
    reload = 1500;
    isShooting = false;
    damage = 50;
    damageD = 50;
    yellow = load_image("yellow.png", false, 0, 0, 0);
    gas = load_image("gas.png", true, 255, 0, 0);
    arial32 = TTF_OpenFont("arial.ttf", 32);
    level = 1;
    //gasPtr = NULL;
  };
  Tower() : Sprite() {type_ = 0; isSet = false;range_=100;};
  Tower(int x, int y, char type) : Sprite(x, y)
  {
    type_ = type;
    isSet = false;
    range_ = 100;
    shootLength = 1000;
    shootTimer = 0;
    reload = 1500;
    isShooting = false;
    damage = 50;
    damageD = 50;
    yellow = load_image("yellow.png", false, 0, 0, 0);
    gas = load_image("gas.png", true, 255, 0, 0);
    arial32 = TTF_OpenFont("arial.ttf", 32);
    level = 1;
    //gasPtr = NULL;
  }

  void step(int, int, int, list<Enemy>&);
  void event(SDL_Event, int, int);
  void set_angle(int, int);
  void draw(int, int);

};

#endif

