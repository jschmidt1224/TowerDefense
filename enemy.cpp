
#include "enemy.h"
#include "bullet.h"
#include <sstream>
#include <SDL\SDL_ttf.h>

extern void draw_text(int, int, std::string, TTF_Font*, SDL_Color, SDL_Surface*);
extern SDL_Surface* screen;

void Enemy::step(int d, list<Path>& P, list<Bullet>& B, list<Gas>& G)
{
  stopTimer += d;
  if(stopTimer > 0)
    Sprite::step(d);
  MyRect r = {0, 0, 0, 0};
  list<Path>::iterator itP;
  list<Bullet>::iterator itB;
  list<Gas>::iterator itG;
  for(itP = P.begin(); itP != P.end(); itP++)
  {
    if(collision_check(*itP, r))
    {
      if(itP->direction == UP)
      {
        speed_.y = -maxSpeed_;
        speed_.x = 0;
      }
      if(itP->direction == DOWN)
      {
        speed_.y = maxSpeed_;
        speed_.x = 0;
      }
      if(itP->direction == LEFT)
      {
        speed_.y = 0;
        speed_.x = -maxSpeed_;
      }
      if(itP->direction == RIGHT)
      {
        speed_.y = 0;
        speed_.x = maxSpeed_;
      }
    }

  }
  for(itB = B.begin(); itB != B.end(); itB++)
  {
    if(collision_check(*itB, r))
    {
      hit(itB->damage, PHYS);
      itB = B.erase(itB);
    }
  }
  for(itG = G.begin(); itG != G.end(); itG++)
  {
    if(collision_check(*itG, r))
    {
      hit(itG->damage/10.0f*d, CHEM);
    }
  }
}

void Enemy::hit(float damage, char type)
{
  health_ -= damage;
}

void Enemy::draw()
{
  Sprite::draw();
  std::stringstream ss;
  TTF_Font* arial32 = TTF_OpenFont("arial.ttf", 32);
  SDL_Color textColor = {0, 0, 0};
  ss << health_;
  //draw_text(0, 0, ss.str(), arial32, textColor, screen);
  TTF_CloseFont(arial32);
}
