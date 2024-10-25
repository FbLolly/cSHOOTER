#include "headers/Menu.h"
#include "headers/Buttons.h"
#include "headers/GameData.h"
#include "headers/defines.h"
#include <raylib.h>

void setMenu(Menu *m, GameData *gd) {
  int i;
  char *str;

  m->title = "Shooter";
  m->titlePos = (Vector2){
      WIDTH / 2.0 -
          MeasureTextEx(gd->titleFont, m->title, TITLESIZE, 1).x / 2.0,
      -HEIGHT / 4.0};

  for (i = 0; i < 2; i++) {
    if (i == 0)
      str = "PLAY";
    else
      str = "QUIT";

    setButton(
        &m->btns[i], gd, str,
        (Vector2){WIDTH / 2.0 -
                      MeasureTextEx(gd->normalFont, str, NORMALSIZE, 1).x / 2.0,
                  HEIGHT / 1.9 + i * HEIGHT / 8.6},
        (Color){80, 80, 80, 180}, LIGHTGRAY);
  }
}

void manageMenu(Menu *m, GameData *gd) {
  int i;

  if (m->titlePos.y <= 100)
    m->titlePos.y += 5 * DELTA;

  for (i = 0; i < 2; i++)
    manageButton(&m->btns[i]);

  if (isButtonPressed(&m->btns[0])) {
    gd->state = GAME;
    return;
  }
  if (isButtonPressed(&m->btns[1])) {
    gd->state = QUIT;
    return;
  }

  BeginDrawing();
  ClearBackground(WHITE);
  DrawTexture(gd->background, 0, 0, RAYWHITE);
  DrawRectangle(0, 0, WIDTH, HEIGHT, (Color){50, 50, 50, 180});

  DrawTextEx(gd->titleFont, m->title,
             (Vector2){m->titlePos.x - NORMALSIZE / 4.0,
                       m->titlePos.y - NORMALSIZE / 8.0},
             TITLESIZE, 1, DARKGRAY);
  DrawTextEx(gd->titleFont, m->title, m->titlePos, TITLESIZE, 1, LIGHTGRAY);

  for (i = 0; i < 2; i++)
    renderButton(&m->btns[i], gd);
  EndDrawing();
}
