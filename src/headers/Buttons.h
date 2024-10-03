#ifndef BUTTONS_H
#define BUTTONS_H

#include "GameData.h"
#include <raylib.h>
typedef struct {
  Rectangle HitBox;
  Rectangle Graphical;
  Color color;
  char *string;

  Vector2 mt;
} Button;

void setButton(Button *b, GameData *gd, char *string, Vector2 TextStart,
               Color color);
bool isButtonPressed(Button *b);
void manageButton(Button *b);
void renderButton(Button *b, GameData *gd);

#endif
