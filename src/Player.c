#include "headers/Player.h"
#include "headers/Enemy.h"
#include "headers/GameData.h"
#include "headers/Particles.h"
#include "headers/defines.h"
#include <raylib.h>

void setPlayer(Player *p) {
  p->HitBox = (Rectangle){WIDTH / 2.0 - 24, HEIGHT - (48 * 2), 48, 48};
  p->shooting = false;
  p->bulletSpeed = 35.0;

  p->money = 0;
  p->score = 0;
}

void managePlayer(Player *p, Enemies *es, GameData *gd) {
  int i, counter = 0;

  if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) {
    p->HitBox.x -= DELTA * 20;

    if (IsKeyDown(KEY_LEFT_SHIFT))
      p->HitBox.x += DELTA * 10;
  }
  if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) {
    p->HitBox.x += DELTA * 20;

    if (IsKeyDown(KEY_LEFT_SHIFT))
      p->HitBox.x -= DELTA * 10;
  }
  if (IsKeyPressed(KEY_SPACE) && !p->shooting) {
    p->shooting = true;
  }

  if (p->HitBox.x < -p->HitBox.width / 2.0) {
    p->HitBox.x = WIDTH - (p->HitBox.width / 2.0);
  }

  if (p->HitBox.x > WIDTH - (p->HitBox.width / 2.0)) {
    p->HitBox.x = -p->HitBox.width / 2.0;
  }

  if (p->shooting) {
    p->bullet.y -= DELTA * p->bulletSpeed;

    if (p->bullet.y <= -p->bullet.height) {
      p->shooting = false;
    }
  } else {
    p->bullet = p->HitBox;
  }

  for (i = 0; i < es->num; i++) {
    if (es->enemies[i].hitbox.y >=
        p->HitBox.y - 20 - es->enemies[i].hitbox.height) {
      if (CheckCollisionRecs(p->HitBox, es->enemies[i].hitbox) ||
          es->enemies[i].hitbox.y >= HEIGHT) {
        gd->state = GAMEOVER;
        return;
      }
    }

    if (es->enemies[i].hitbox.y > -es->enemies[i].hitbox.height) {
      if (CheckCollisionRecs(p->bullet, es->enemies[i].hitbox)) {
        es->enemies[i].health--;

        if (es->enemies[i].health <= 0) {
          p->money += es->enemies[i].type;
          if (resetEnemy(&es->enemies[i], p->score) == 1) {
            addEnemies(es);
          }
          p->score++;
        } else {
          p->shooting = false;
          setParticles(es->enemies[i].particles, LIGHTGRAY, LIGHTGRAY, BLACK,
                       TOP);
          startParticles(
              es->enemies[i].particles,
              (Vector2){
                  es->enemies[i].hitbox.x + es->enemies[i].hitbox.width / 2.0,
                  es->enemies[i].hitbox.y + es->enemies[i].hitbox.height / 2.0},
              &es->enemies[i].active);
        }
      }
    }
  }
}

void renderPlayer(Player *p) {
  DrawRectangleRounded(p->bullet, 0.25, 10, GRAY);

  DrawRectangleRounded(p->HitBox, 0.25, 10, LIGHTGRAY);
}
