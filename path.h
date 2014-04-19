
#ifndef PATH_H
#define PATH_H

#define UP 1
#define DOWN 2
#define LEFT 4
#define RIGHT 8

class Path : public Sprite
{
public:
  int direction;
  int condition;
  Path(int x, int y, int d) : Sprite(x, y)
  {
    direction = d;
    position_.w = 8;
    position_.h = 8;
  };


};






#endif
