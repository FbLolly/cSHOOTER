#ifndef MENU_H
#define MENU_H

#include "Buttons.h"
#include "GameData.h"
#include <raylib.h>
typedef struct {
  Button btns[2];
  char *title;
  Vector2 titlePos;
} Menu;

void setMenu(Menu *m, GameData *gd);
void manageMenu(Menu *m, GameData *gd);

#endif
