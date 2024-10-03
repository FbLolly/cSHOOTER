#include "headers/Shop.h"
#include "headers/Buttons.h"
#include "headers/Enemy.h"
#include "headers/GameData.h"
#include "headers/defines.h"
#include <raylib.h>

void setShop(Shop *shop, GameData *gd) {
  int i;
  char *str;
  Vector2 pos, mt;

  shop->animX = WIDTH;

  for (i = 0; i < 4; i++) {
    switch (i) {
    case 0:
      str = "Fast shot 40$";
      shop->prices[i] = 40;
      pos = (Vector2){WIDTH / 4.0, HEIGHT / 4.0};
      break;
    case 1:
      str = "canc Enemy 80$";
      shop->prices[i] = 80;
      pos = (Vector2){WIDTH / 2.0 + WIDTH / 4.0, HEIGHT / 4.0};
      break;
    case 2:
      str = "Weak Enemy 60$";
      shop->prices[i] = 60;
      pos = (Vector2){WIDTH / 4.0, HEIGHT / 2.0 + HEIGHT / 4.0};
      break;
    case 3:
      str = "2x canc 150$";
      shop->prices[i] = 150;
      pos = (Vector2){WIDTH / 2.0 + WIDTH / 4.0, HEIGHT / 2.0 + HEIGHT / 4.0};
      break;
    }

    mt = MeasureTextEx(gd->normalFont, str, NORMALSIZE, 1);
    pos.x -= mt.x / 2.0;
    pos.y -= mt.y / 2.0;

    pos.x += WIDTH;

    setButton(&shop->btns[i], gd, str, pos, PURPLE);
  }
}

void manageShop(Shop *shop, Player *p, Enemies *es, GameData *gd) {
  int i, ii;
  bool stop = true;
  bool direction; // 0->left, 1->right

  if (gd->state == SHOP) {
    if (shop->animX >= 10) {
      shop->animX -= DELTA * 50;
      stop = false;
      direction = 0;
    }
  } else if (gd->state == GAME) {
    if (shop->animX <= WIDTH) {
      shop->animX += DELTA * 50;
      stop = false;
      direction = 1;
    }
  }

  if (!stop) {
    for (i = 0; i < 4; i++) {
      if (shop->animX >= 10 && shop->animX <= WIDTH) {
        if (direction == 0) {
          shop->btns[i].HitBox.x -= DELTA * 50;
          shop->btns[i].Graphical.x -= DELTA * 50;

          if (shop->animX <= 10)
            shop->animX = 10;
        } else if (direction == 1) {
          shop->btns[i].HitBox.x += DELTA * 50;
          shop->btns[i].Graphical.x += DELTA * 50;
        }
      }
    }
  }

  if (gd->state == SHOP || shop->animX < WIDTH) {
    for (i = 0; i < 4; i++) {
      manageButton(&shop->btns[i]);

      if (isButtonPressed(&shop->btns[i])) {

        if (p->money >= shop->prices[i]) {
          p->money -= shop->prices[i];
          switch (i) {
          case 0:
            p->bulletSpeed += 5;
            break;
          case 1:
            removeEnemies(es);
            break;
          case 2:
            for (ii = 0; ii < es->num; i++) {
              if (es->enemies[i].type > 1)
                es->enemies[i].type--;
            }
            break;
          case 3:
            removeEnemies(es);
            removeEnemies(es);
            break;
          }
        }
      }
    }
  }
}

void renderShop(Shop *shop, GameData *gd) {
  int i;

  DrawRectangleRounded((Rectangle){shop->animX, 10, WIDTH - 20, HEIGHT - 20},
                       0.05, 50, (Color){180, 180, 180, 180});
  if (gd->state == SHOP || shop->animX < WIDTH) {
    for (i = 0; i < 4; i++) {
      renderButton(&shop->btns[i], gd);
    }
  }
}
