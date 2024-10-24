#ifndef GAME_H
#define GAME_H

#include "Enemy.h"
#include "GameData.h"
#include "Player.h"
#include "Shop.h"
#include <raylib.h>

typedef struct {
  Player player;

  Enemies enemies;
  Shop shop;

  Texture warningTexture;
} Game;

void setGame(Game *game, GameData *gd);
void manageGame(Game *game, GameData *gd);

void renderSxPanel(GameData *gd, int score, int money);

void renderPause(Game *game, GameData *gd);

#endif
