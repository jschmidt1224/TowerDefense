
#include "ui.h"
#include <string>
#include "SDL/SDL_ttf.h"

extern void draw_rect(int, int, int, int, int, int, int, SDL_Surface*);
extern void draw_text(int, int, std::string, TTF_Font*, SDL_Color, SDL_Surface*);
extern SDL_Surface* screen;
TTF_Font* arial18 = TTF_OpenFont("arial.ttf", 18);
TTF_Font* arial32 = TTF_OpenFont("arial.ttf", 32);
SDL_Color textColor = {0, 0, 0};

void UI::draw()
{
  Sprite::draw();
  draw_rect(768, 0, 128, 896, 0, 255, 255, screen);
  draw_rect(768, 0, 128, 64, 0, 200, 200, screen);
  draw_text(768+16, 16, "MENU", arial32, textColor, screen);
}
