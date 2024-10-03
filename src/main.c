#include <raylib.h>
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

  bool exit = false, counter = false;

  srand(time(NULL));

  InitWindow(WIDTH, HEIGHT, "Game");
  SetConfigFlags(FLAG_VSYNC_HINT);

  setGameData(&gameData);
  setMenu(&menu, &gameData);

  game.enemies.enemies = NULL;

  while (!exit) {
    if (WindowShouldClose() && !IsKeyDown(KEY_ESCAPE)) {
      goto end;
    }
    if (IsKeyDown(KEY_ESCAPE)) {
      switch (gameData.state) {
      case SHOP:
        gameData.state = GAME;
      default:
        gameData.state = MENU;
        break;
      }
    }

    if (IsKeyPressed(KEY_ENTER)) {
      if (gameData.state == GAME)
        gameData.state = SHOP;
      else if (gameData.state == SHOP)
        gameData.state = GAME;
    }

    switch (gameData.state) {
    case MENU:
      counter = false;
      manageMenu(&menu, &gameData);
      break;
    case GAMEOVER:
    case SHOP:
      manageGame(&game, &gameData);
    case GAME:
      if (!counter) {
        setGame(&game, &gameData);
        counter = true;
      }

      manageGame(&game, &gameData);
      break;
    case QUIT:
      exit = true;
      break;
    default:
      break;
    }
    gameData.frameCounter += 1 * DELTA;
  }

end:
  freeEnemies(&game.enemies);
  UnloadFont(gameData.titleFont);
  UnloadFont(gameData.normalFont);

  return 0;
}
