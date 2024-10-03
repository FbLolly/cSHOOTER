#ifndef GAMEDATA_H
#define GAMEDATA_H

#include "defines.h"
#include <raylib.h>

typedef struct {
  GameState state;
  float frameCounter;

  Font titleFont;  // 32 px
  Font normalFont; // 16 px

  bool pause;

  Texture background;
} GameData;

void setGameData(GameData *gd);
void gameOver(int lastScore, GameData *gd);

#endif
