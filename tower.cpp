
#include "tower.h"
#include "enemy.h"
#include <cmath>
#include <list>
#include <sstream>
#include <string>
#include <SDL\SDL_ttf.h>

extern list<Gas> gases;
extern double get_distance(MyRect, MyRect);
extern bool hasTower;
extern void draw_lightning(int, int, int, int, int,SDL_Surface*);
extern SDL_Surface* load_image(std::string filename, bool trans = false, int r = 0, int g = 0, int b = 0);
extern void draw_text(int, int, std::string, TTF_Font*, SDL_Color, SDL_Surface*);
extern SDL_Surface* screen;
extern void create_bullet(int, int, int, bool, float, Enemy*);
extern void draw_surface(MyRect, SDL_Surface*, SDL_Surface*, SDL_Rect*);
extern int money;

void Tower::step(int dTime, int mouseX, int mouseY, list<Enemy>& E)
{
  Sprite::step(dTime);
  MyRect tmp;
  double angle;
  shootTimer += dTime;
  list<Enemy>::iterator it = E.begin();
  if (!isSet)
  {
    position_.x = (mouseX / 32) * 32;
    position_.y = (mouseY / 32) * 32;
  }
  double minDistance = 10000;
  for(it = E.begin(); it != E.end(); it++)
  {
    memcpy(&tmp, &(it->position_), sizeof(tmp));
    if(get_distance(position_, tmp) < minDistance)
    {
      minDistance = get_distance(position_, it->get_position());
      if(get_distance(position_, it->get_position()) < range_)
        target = &(*it);
    }
  }
  if(minDistance < range_)
  {
    set_angle(target->get_position().x, target->get_position().y);
    if(canShoot && isSet)
    {
      canShoot = false;
      isShooting = true;
      shootTimer = 0;
      if(type_ == EE)
        target->hit(damage, type_);
      if(type_ == ME)
        create_bullet(position_.x, position_.y, damage, false, 200, target);
      //if(target->health_ <= 0)
        //isShooting = false;
    }
  }
  if(shootTimer > shootLength)
  {
    isShooting = false;
  }
  if(shootTimer > reload)
  {
    canShoot = true;
    shootTimer = 0;
  }
}

void Tower::event(SDL_Event event, int mouseX, int mouseY)
{
  if(event.type == SDL_MOUSEBUTTONDOWN)
  {
    if (event.button.button == SDL_BUTTON_RIGHT)
    {
      //isSet = true;
      hasTower = false;
      if(type_ == ChE && !isSet)
      {
        Gas g(position_.x - 64-32-16, position_.y-64-32-16);
        g.surface = load_image("gas.png", true, 255, 0, 0);
        SDL_SetAlpha(g.surface, SDL_SRCALPHA, 255/10);
        //MyRect r = {0, 0, 200, 200}
        g.clip.x = 0;
        g.clip.y = 0;
        g.clip.w = 300;
        g.clip.h = 300;
        gases.push_front(g);
        gasIt = gases.begin();

      }
      isSet = true;
    }
    if (event.button.button == SDL_BUTTON_LEFT)
    {
      if(mouseX > position_.x && mouseX < position_.x + 32)
      {
        if(mouseY > position_.y && mouseY < position_.y + 32)
        {
          if(isSet)
          {
            if(money >= 50)
            {
              level++;
              damage = damageD * level * level;
              if(type_ == ChE)
                gasIt->levelup(level);
              money -= 50;
            }
          }
        }
      }
    }
  }
}

void Tower::set_angle(int x, int y)
{
  double angle;
  angle = atan2(position_.y + 16 - y, x - position_.x - 16);
  angle /= M_PI / 180;
  if(angle < 0)
    angle += 360;
  angle /= 360;
  angle *= 64;
  angle = round(angle);
  angle *= 32;
  if (angle == 2048)
    angle = 0;
  clip.x = angle;
}

void Tower::draw(int mouseX, int mouseY)
{
  std::stringstream ss;
  if(isShooting && type_ == EE)
  {
    //SDL_Surface* yellow = load_image("yellow.png");
    //TTF_Font* arial32 = TTF_OpenFont("arial.ttf", 32);
    SDL_Color textColor = {0, 0, 0};
    draw_lightning(position_.x + 16, position_.y + 16, target->position_.x + 8, target->position_.y + 8, 10, yellow);
    draw_lightning(position_.x + 16, position_.y + 16, target->position_.x + 8, target->position_.y + 8, 15, yellow);
    //SDL_FreeSurface(yellow);
    ss << shootTimer;
    //TTF_CloseFont(arial32);
    //draw_text(0, 0, ss.str(), arial32, textColor, screen);

  }
  if(mouseX > position_.x && mouseX < position_.x + 32)
  {
    if(mouseY > position_.y && mouseY < position_.y + 32)
    {
      std::stringstream ss;
      ss.str(std::string());
      ss << "Level: " << level;
      TTF_Font* arial18 = TTF_OpenFont("arial.ttf", 18);
      SDL_Color textColor = {0, 0, 0};
      draw_text(768+16, 64 + 256, ss.str(), arial18, textColor, screen);
      ss.str(std::string());
      ss << "Damage: " << (type_ == ChE ? .1* level*level : damage);
      draw_text(768+16, 64 + 276, ss.str(), arial18, textColor, screen);
      ss.str(std::string());
      ss << "Cost: " << 20 * level;
      draw_text(768+16, 64 + 296, ss.str(), arial18, textColor, screen);
      TTF_CloseFont(arial18);
    }
  }
  Sprite::draw();
}
