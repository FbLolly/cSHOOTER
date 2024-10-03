#include "headers/Game.h"
#include "headers/Enemy.h"
#include "headers/GameData.h"
#include "headers/Player.h"
#include "headers/Shop.h"
#include "headers/defines.h"
#include <raylib.h>

void setGame(Game *game, GameData *gd) {
  setEnemies(&game->enemies);
  setPlayer(&game->player);
  setShop(&game->shop, gd);
}

void manageGame(Game *game, GameData *gd) {
  if (gd->state != GAMEOVER && gd->state != SHOP) {
    managePlayer(&game->player, &game->enemies, gd);
    manageEnemies(&game->enemies);
  }
  manageShop(&game->shop, &game->player, &game->enemies, gd);

  BeginDrawing();
  ClearBackground(WHITE);
  renderPlayer(&game->player);
  renderEnemies(&game->enemies);
  renderSxPanel(gd, game->player.score, game->player.money);

  if (gd->state == GAMEOVER) {
    DrawRectangleRec((Rectangle){0, 0, WIDTH, HEIGHT},
                     (Color){180, 180, 180, 180});
    gameOver(game->player.score, gd);
  }
  renderShop(&game->shop, gd);

  EndDrawing();
}

void renderSxPanel(GameData *gd, int score, int money) {
  float big;
  Vector2 mt = MeasureTextEx(gd->normalFont, TextFormat("Score: %d", score),
                             NORMALSIZE, 1);
  Vector2 mt2 = MeasureTextEx(gd->normalFont, TextFormat("Money: %d", money),
                              NORMALSIZE, 1);

  mt.y += mt2.y;
  big = mt2.x;

  if (mt.x > mt2.x)
    big = mt.x;

  DrawRectangleRounded((Rectangle){10, 10, 40 + big, 65 + mt.y}, 0.25, 50,
                       (Color){180, 180, 180, 180});

  DrawTextEx(gd->normalFont, TextFormat("Score: %d", score), (Vector2){30, 30},
             NORMALSIZE, 1, (Color){50, 50, 50, 180});
  DrawTextEx(gd->normalFont, TextFormat("Money: %d", money),
             (Vector2){30, 60 + mt.y - mt2.y}, NORMALSIZE, 1,
             (Color){50, 50, 50, 180});
}
