
#include "bullet.h"

extern double get_distance(MyRect, MyRect);

Bullet::Bullet(int x, int y, int dam, bool expl, float speed,Sprite* tar)
{
  Sprite(x, y);
  position_.x = x;
  position_.y = y;
  position_.w = 6;
  position_.h = 6;
  damage = dam;
  explode = expl;
  target = tar;
  maxSpeed = speed;
}

void Bullet::step(int dt)
{
  double dist = get_distance(position_, target->position_);
  speed_.x = target->position_.x - position_.x;
  speed_.x /= dist;
  speed_.y = target->position_.y - position_.y;
  speed_.y /= dist;
  speed_.x *= maxSpeed;
  speed_.y *= maxSpeed;

  Sprite::step(dt);
}
