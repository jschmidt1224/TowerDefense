


#ifndef INIT_H
#define INIT_H

#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_image.h"
#include "Rectangle.h"
#include "enemy.h"
#include "bullet.h"
#include <list>



extern SDL_Surface* screen;
extern list<Bullet> bullets;

bool init(int screen_height, int screen_width, int screen_bpp)
{
  if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
    return true;

  if ((screen = SDL_SetVideoMode(screen_width, screen_height, screen_bpp, SDL_SWSURFACE)) == NULL)
    return true;

  SDL_WM_SetCaption("Tower Defense", NULL);

  TTF_Init();

  return false;
}

SDL_Surface* load_image(std::string filename, bool trans = false, int r = 0, int g = 0, int b = 0)
{
    SDL_Surface* image = NULL;
    SDL_Surface* optimized = NULL;
    image = IMG_Load(filename.c_str()); //loads image
    if (image != NULL)
    {
        optimized = SDL_DisplayFormat(image);
        SDL_FreeSurface(image);
    }
    if (optimized != NULL && trans)
    {
        Uint32 colorkey = SDL_MapRGB(optimized->format, r, g, b);
        SDL_SetColorKey(optimized, SDL_SRCCOLORKEY, colorkey);
    }
    return optimized;
}

void draw_surface(MyRect X, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL)
{
    SDL_Rect offset; //creates and set values for offset
    offset.x = (int)round(X.x);
    offset.y = (int)round(X.y);
    SDL_BlitSurface(source, clip, destination, &offset);
}

void draw_MyRect(int x, int y, int w, int h, int R, int G, int B, SDL_Surface* dest)
{
    SDL_Rect r = {x, y, w, h};
    SDL_FillRect(dest, &r, SDL_MapRGB(screen->format, R, G, B));
}

void draw_text(int x, int y, std::string str, TTF_Font* font, SDL_Color textColor, SDL_Surface* destination)
{
  SDL_Surface* tmp;
  MyRect X = {x, y, 0, 0};
  tmp = TTF_RenderText_Solid(font, str.c_str(), textColor);
  draw_surface(X, tmp, screen);
  SDL_FreeSurface(tmp);
}

double get_distance(MyRect A, MyRect B)
{
  return sqrt(pow(A.x - B.x,2) + pow(A.y - B.y,2));
}

void draw_line(float x1, float y1, float x2, float y2, SDL_Surface* pixel)
{
  // Bresenham's line algorithm
  const bool steep = (fabs(y2 - y1) > fabs(x2 - x1));
  if(steep)
  {
    std::swap(x1, y1);
    std::swap(x2, y2);
  }
  if(x1 > x2)
  {
    std::swap(x1, x2);
    std::swap(y1, y2);
  }
  const float dx = x2 - x1;
  const float dy = fabs(y2 - y1);

  float error = dx / 2.0f;
  const int ystep = (y1 < y2) ? 1 : -1;
  int y = (int)y1;

  const int maxX = (int)x2;

  for(int x=(int)x1; x<maxX; x++)
  {
    if(steep)
    {
      MyRect tmp = {y, x, 0, 0};
      draw_surface(tmp, pixel, screen);
      //SetPixel(y,x, color);
    }
    else
    {
      MyRect tmp = {x, y, 0, 0};
      draw_surface(tmp, pixel, screen);
      //SetPixel(x,y, color);
    }

    error -= dy;
    if(error < 0)
    {
      y += ystep;
      error += dx;
    }
  }
}

void draw_lightning(int x1, int y1, int x2, int y2, int seg, SDL_Surface* pixel)
{
  //srand(time(NULL));
  double dX = x2 - x1;
  double dY = y2 - y1;
  double stepX = dX/seg;
  double stepY = dY/seg;
  double rnd;
  int x = x1;
  int y = y1;
  int xprev = x1;
  int yprev = y1;
  for(int i = 1; i < seg; i++)
  {
    rnd = rand();
    x = x1 + i*stepX;
    y = y1 + i*stepY;
    x += rand() % 20 - 10;
    y += rand() % 20 - 10;
    draw_line(xprev, yprev, x, y, pixel);
    xprev = x;
    yprev = y;
  }
  draw_line(xprev, yprev, x2, y2, pixel);

}

void create_bullet(int x, int y, int damage, bool exp, float speed, Enemy* en)
{
  Bullet b(x, y, damage, exp, speed, en);
  b.surface = load_image("bullet.png");
  SDL_Rect  r = {0, 0, 10, 10};
  b.clip = r;
  bullets.push_back(b);
}

/*void create_gas(int x, int y, int damage)
{
  Bullet b(x, y, damage, exp, speed, en);
  b.surface = load_image("bullet.png");
  SDL_Rect  r = {0, 0, 10, 10};
  b.clip = r;
  bullets.push_back(b);
}*/

#endif
