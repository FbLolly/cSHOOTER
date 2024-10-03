#ifndef SHOP_H
#define SHOP_H

#include "Buttons.h"
#include "Player.h"

typedef struct {
  Button btns[4];
  int prices[4];

  Texture txtr[4];

  float animX;
} Shop;

void setShop(Shop *shop, GameData *gd);
void manageShop(Shop *shop, Player *p, Enemies *es, GameData *gd);
void renderShop(Shop *shop, GameData *gd);

#endif
