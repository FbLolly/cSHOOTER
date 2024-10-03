#include "headers/GameData.h"
#include "headers/defines.h"
#include <raylib.h>
#include <time.h>

void setGameData(GameData *gd) {
  gd->state = MENU;
  gd->frameCounter = 0;

  gd->titleFont = LoadFontEx(TITLEFONT, TITLESIZE, NULL, 0);
  gd->normalFont = LoadFontEx(NORMALFONT, NORMALSIZE, NULL, 0);

  gd->pause = false;
  gd->background = LoadTextureFromImage(LoadImage("images/b2.png"));
}

void gameOver(int lastScore, GameData *gd) {
  if (IsKeyPressed(KEY_ENTER)) {
    gd->state = MENU;
    return;
  }

  DrawTextEx(
      gd->titleFont, "GAME OVER",
      (Vector2){WIDTH / 2.0 -
                    MeasureTextEx(gd->titleFont, "GAME OVER", TITLESIZE, 1).x /
                        2.0,
                WIDTH / 50.0},
      TITLESIZE, 1, BLACK);

  DrawTextEx(gd->normalFont, TextFormat("Last score: %d", lastScore),
             (Vector2){WIDTH / 2.0 - MeasureTextEx(gd->normalFont,
                                                   TextFormat("Last score: %d",
                                                              lastScore),
                                                   NORMALSIZE, 1)
                                             .x /
                                         2.0,
                       WIDTH / 4.0},
             NORMALSIZE, 1, BLACK);

  DrawTextEx(gd->normalFont, "Press Enter To Continue",
             (Vector2){WIDTH / 2.0 - MeasureTextEx(gd->normalFont,
                                                   "Press Enter To Continue",
                                                   NORMALSIZE, 1)
                                             .x /
                                         2.0,
                       WIDTH / 3.0},
             NORMALSIZE, 1, BLACK);
}
