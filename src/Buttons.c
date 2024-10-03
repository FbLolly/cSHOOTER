#include "headers/Buttons.h"
#include "headers/GameData.h"
#include "headers/defines.h"
#include <raylib.h>

void setButton(Button *b, GameData *gd, char *string, Vector2 pos,
               Color color) {
  b->mt = MeasureTextEx(gd->normalFont, string, NORMALSIZE, 1);

  b->HitBox = (Rectangle){pos.x - (b->mt.x / 2), pos.y, b->mt.x * 2, b->mt.y};
  b->Graphical =
      (Rectangle){pos.x + b->mt.x / 2.0, pos.y + b->mt.y / 2.0, 0, 0};
  b->color = color;
  b->string = string;
}

bool isButtonPressed(Button *b) {
  if (CheckCollisionPointRec(GetMousePosition(), b->HitBox) &&
      IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
    return true;
  }

  return false;
}

void manageButton(Button *b) {
  if (CheckCollisionPointRec(GetMousePosition(), b->HitBox)) {
    if (b->Graphical.x >= b->HitBox.x)
      b->Graphical.x -= DELTA / 50 * b->HitBox.width * 2;
    if (b->Graphical.y >= b->HitBox.y)
      b->Graphical.y -= DELTA / 50 * b->HitBox.height * 2;
    if (b->Graphical.width <= b->HitBox.width)
      b->Graphical.width += DELTA / 50 * b->HitBox.width * 4;
    if (b->Graphical.height <= b->HitBox.height)
      b->Graphical.height += DELTA / 50 * b->HitBox.height * 4;
  } else {
    if (b->Graphical.x < b->HitBox.x + (b->HitBox.width / 2.0))
      b->Graphical.x += DELTA / 20 * b->HitBox.width;
    if (b->Graphical.y < b->HitBox.y + (b->HitBox.height / 2.0))
      b->Graphical.y += DELTA / 20 * b->HitBox.height;
    if (b->Graphical.width > 0)
      b->Graphical.width -= DELTA / 20 * b->HitBox.width * 2;
    if (b->Graphical.height > 0)
      b->Graphical.height -= DELTA / 20 * b->HitBox.height * 2;
  }
}

void renderButton(Button *b, GameData *gd) {
  DrawRectangleRounded(b->Graphical, 0.5, 50, b->color);
  DrawTextEx(gd->normalFont, b->string,
             (Vector2){b->HitBox.x + b->HitBox.width / 2.0 - b->mt.x / 2.0,
                       b->HitBox.y + 5},
             NORMALSIZE, 1, BLACK);
}
