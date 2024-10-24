#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "headers/Enemy.h"
#include "headers/Game.h"
#include "headers/GameData.h"
#include "headers/Menu.h"
#include "headers/defines.h"

int main() {
  GameData gameData;
  Menu menu;
  Game game;

  bool exit = false, counter = false, menuCount = false;

  srand(time(NULL));
  SetTargetFPS(240);

  InitWindow(WIDTH, HEIGHT, "Game");
  SetConfigFlags(FLAG_VSYNC_HINT);

  // Early loading warning texture to avoid reloading it
  game.warningTexture = LoadTextureFromImage(LoadImage(WARNING));

  setGameData(&gameData);

  game.enemies.enemies = NULL;

  while (!exit) {
    if (WindowShouldClose() && !IsKeyDown(KEY_ESCAPE)) {
      goto end;
    }

    switch (gameData.state) {
    case MENU:
      if (!menuCount) {
        setMenu(&menu, &gameData);
        menuCount = true;
      }

      counter = false;
      manageMenu(&menu, &gameData);
      break;
    case PAUSE:
    case GAMEOVER:
    case SHOP:
      manageGame(&game, &gameData);
    case GAME:
      if (!counter) {
        setGame(&game, &gameData);
        counter = true;
      }
      menuCount = false;

      manageGame(&game, &gameData);
      break;
    case QUIT:
      exit = true;
      break;
    default:
      break;
    }

    if (IsKeyPressed(KEY_ESCAPE)) {
      switch (gameData.state) {
      case PAUSE:
      case SHOP:
        break;
      default:
        gameData.state = MENU;
        break;
      }
    }

    if (IsKeyPressed(KEY_ENTER) && gameData.state == GAME) {
      gameData.state = SHOP;
    }
    if (IsKeyPressed(KEY_P) && gameData.state == GAME) {
      gameData.state = PAUSE;
    }
    if (IsKeyDown(KEY_ENTER) && gameData.state == GAMEOVER) {
      gameData.state = MENU;
    }

    if (IsKeyDown(KEY_ESCAPE)) {
      switch (gameData.state) {
      case PAUSE:
      case SHOP:
        gameData.state = GAME;
        break;
      default:
        break;
      }
    }

    gameData.frameCounter += 1 * DELTA;
  }

end:
  freeEnemies(&game.enemies);
  UnloadTexture(gameData.background);
  UnloadTexture(game.warningTexture);
  UnloadFont(gameData.titleFont);
  UnloadFont(gameData.normalFont);

  return 0;
}
