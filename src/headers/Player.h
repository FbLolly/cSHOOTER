#ifndef PLAYER_H
#define PLAYER_H

#include "Enemy.h"
#include "GameData.h"
#include <raylib.h>

typedef struct {
  Rectangle HitBox;
  Texture txr;
  Rectangle bullet;

  float bulletSpeed;
  bool shooting;

  int score;
  int money;
} Player;

void setPlayer(Player *p);
void managePlayer(Player *p, Enemies *es, GameData *gd);
void renderPlayer(Player *p);

#endif
