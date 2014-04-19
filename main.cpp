
#include <cmath>
#include <fstream>
#include <string>
#include <sstream>
#include <list>
#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_image.h"
#include "init.h"
#include "timer.h"
#include "Rectangle.h"
#include "sprite.h"
#include "tower.h"
#include "enemy.h"
#include "path.h"
#include "bullet.h"


#define MESSAGE_MAX 255

using namespace std;


SDL_Surface* screen;
SDL_Surface* background;
MyRect Zero = {0, 0, 0, 0};
SDL_Event event;
bool hasTower = false;
fstream output;
list<Sprite> sprites;
list<Sprite>::iterator itSpr;
list<Tower> towers;
list<Tower>::iterator itTow;
list<Enemy> enemies;
list<Enemy>::iterator itEn;
list<Path> paths;
list<Path>::iterator itPath;
list<Bullet> bullets;
list<Bullet>::iterator itBul;
list<Gas> gases;
list<Gas>::iterator itGas;
int money = 1000;
int enemyCount = 0;
int enemyTime = 2000;
double totalTime = 0;
float enemyProb = 1;
float randomVal;


int main(int argc, char* args[])
{
  bool quit;
  if (init(768, 896, 32))
    return 1;

  Timer delta;
  stringstream ss;
  int mouseX, mouseY;
  double angle;
  SDL_Surface* tower = load_image("test_strip64.png", true);
  SDL_Surface* black = load_image("black.png");
  SDL_Surface* yellow = load_image("yellow.png");
  int enemyTimer = 0;

  Enemy test(738 + 8, 768, 200, 0, 0 ,0);
  test.surface = load_image("enemy.png");
  background = load_image("background.png");
  SDL_Rect clipTest = {0, 0, 24, 24};
  memcpy(&(test.clip), &clipTest, sizeof(clipTest));

  enemies.push_back(test);

  Path path(760 - 16, 576, LEFT);
  path.surface = load_image("path.png");
  path.clip = clipTest;
  paths.push_back(path);
  MyRect tmpr = {224, 576 + 23 - 16, 8, 8};
  path.set_position(tmpr);
  path.direction = UP;
  paths.push_back(path);
  path.direction = LEFT;
  tmpr.x = 254 - 17;
  tmpr.y = 224;
  path.set_position(tmpr);
  paths.push_back(path);
  tmpr.x = 64;
  tmpr.y = 256- 9 - 16;
  path.direction = UP;
  path.set_position(tmpr);
  paths.push_back(path);

  output.open("output.txt", fstream::out | fstream::trunc);
  output << "Output:" << endl;

  TTF_Font* arial18 = TTF_OpenFont("arial.ttf", 18);
  TTF_Font* arial32 = TTF_OpenFont("arial.ttf", 32);
  SDL_Color textColor = {0, 0, 0};

  delta.start();

  while(quit == false)
  {
    while(SDL_PollEvent(&event))
    {
      if(event.type == SDL_QUIT)
      {
        quit = true;
      }
      if(event.type == SDL_MOUSEBUTTONDOWN)
      {
        if(event.button.button == SDL_BUTTON_LEFT)
        {
          if(money >=20 && !hasTower)
          {
            if(mouseX > 800 && mouseX < 864 && mouseY > 96 && mouseY < 96+64 && !hasTower)
            {
              Tower tmp(100, 100, ME);
              tmp.surface = load_image("ME_Tower.png", true);
              SDL_Rect tmpr = {0, 0, 31, 32};
              tmp.clip = tmpr;
              towers.push_back(tmp);
              money -= 20;
              hasTower = true;
            }
            if(mouseX > 800 && mouseX < 864 && mouseY > 96 + 72 && mouseY < 96+64+72 && !hasTower)
            {
              Tower tmp(100, 100, EE);
              tmp.surface = load_image("EE_Tower.png", true);
              SDL_Rect tmpr = {0, 0, 31, 32};
              tmp.clip = tmpr;
              towers.push_back(tmp);
              money -= 20;
              hasTower = true;
            }

            if(mouseX > 800 && mouseX < 864 && mouseY > 96 + 72 +72 && mouseY < 96+64+72+72 && !hasTower)
            {
              Tower tmp(100, 100, ChE);
              tmp.surface = load_image("ChE_Tower.png", true);
              SDL_Rect tmpr = {0, 0, 31, 32};
              tmp.clip = tmpr;
              towers.push_back(tmp);
              money -= 20;
              hasTower = true;
            }
          }
        }
      }
      for (itTow = towers.begin(); itTow != towers.end(); itTow++)
      {
        itTow->event(event, mouseX, mouseY);
      }
    }
    SDL_GetMouseState(&mouseX, &mouseY);
    //perform step etc.

    for (itTow = towers.begin(); itTow != towers.end(); itTow++)
    {
      itTow->step(delta.get_ticks(), mouseX, mouseY, enemies);
    }
    for (itBul = bullets.begin(); itBul != bullets.end(); itBul++)
    {
      itBul->step(delta.get_ticks());
      if(itBul->position_.x < 2)
        itBul = bullets.erase(itBul);
    }
    for (itEn = enemies.begin(); itEn != enemies.end(); itEn++)
    {
      itEn->step(delta.get_ticks(), paths, bullets, gases);
      if(itEn->health_ <= 0)
      {
        money += itEn->maxHealth_ / 5;
        itEn = enemies.erase(itEn);
      }
      if(itEn->position_.y < -32)
      {
        itEn = enemies.erase(itEn);
      }
    }

    enemyTimer += delta.get_ticks();
    totalTime += delta.get_ticks()/1000.0f;
    if(enemyTimer > enemyTime)
    {
      enemyCount++;
      enemyProb = max(sin(2 * M_PI / 10 *totalTime), (double)0.0);
      test.health_ *= pow(2, 1/50.0f);
      randomVal = rand()/(float)RAND_MAX;
      if(randomVal < enemyProb)
      {
        enemies.push_back(test);
        enemyTimer = 0;
        enemyTime -= 10;
      }
    }




    //restart timer
    delta.start();

    //draw
    ss.str(string());
    itEn = enemies.begin();
    ss << "X: " << mouseX << "   Y: " << mouseY << "   " << itEn->health_ << "   ";

    draw_MyRect(0, 0, 896, 896, 255, 255, 255, screen);

    draw_surface(Zero, background, screen);
    MyRect MyRect = {50, 50, 0, 0};
    draw_text(500-200+64, 50, ss.str(), arial18, textColor, screen);
    draw_MyRect(768, 0, 128, 896, 0, 255, 255, screen);
    draw_MyRect(768, 0, 128, 64, 0, 200, 200, screen);
    draw_text(768+16, 16, "MENU", arial32, textColor, screen);
    ss.str(string());
    ss << "Money: " << randomVal;
    draw_text(768+16, 16 + 32 + 16, ss.str(), arial18, textColor, screen);

    //ME
    draw_MyRect(800, 96, 64, 64, 255, 0, 0, screen);
    SDL_Rect tmpr = {0, 0, 32, 32};
    MyRect.x = 768 + 32 + 32 - 16;
    MyRect.y = 64 + 32 + 32 -16;
    draw_surface(MyRect, tower, screen, &tmpr);
    //EE
    draw_MyRect(800, 96 + 72, 64, 64, 0, 0, 128, screen);
    MyRect.x = 768 + 32 + 32 - 16;
    MyRect.y = 64 + 32 + 32 -16 + 72;
    draw_surface(MyRect, tower, screen, &tmpr);
    //Che
    draw_MyRect(800, 96 + 72 + 72, 64, 64, 34, 177, 76, screen);
    MyRect.x = 768 + 32 + 32 - 16;
    MyRect.y = 64 + 32 + 32 -16 + 72 + 72;
    draw_surface(MyRect, tower, screen, &tmpr);
    //draw_lightning(0, 0, 500, 500, 50, yellow);
    //test.draw();

    for (itEn = enemies.begin(); itEn != enemies.end(); itEn++)
    {
      itEn->draw();
    }
    for (itPath = paths.begin(); itPath != paths.end(); itPath++)
    {
      itPath->draw();
    }
    for (itBul = bullets.begin(); itBul != bullets.end(); itBul++)
    {
      itBul->draw();
    }
    for (itGas = gases.begin(); itGas != gases.end(); itGas++)
    {
      itGas->draw();
    }
    for (itTow = towers.begin(); itTow != towers.end(); itTow++)
    {
      itTow->draw(mouseX, mouseY);
    }
    SDL_Flip(screen);
    //SDL_Delay(10);

  }
  SDL_Quit();
  SDL_FreeSurface(background);
  TTF_Quit();
  output.close();
  return 0;
}
