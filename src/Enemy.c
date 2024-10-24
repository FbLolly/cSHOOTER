#include "headers/Enemy.h"
#include "headers/Particles.h"
#include "headers/defines.h"
#include <assert.h>
#include <raylib.h>
#include <stdlib.h>

void setEnemy(Enemy *e) {
  int i;

  e->type = 1;
  e->hitbox = (Rectangle){(float)(rand() % (WIDTH - 48)),
                          -1 * (float)(rand() % (HEIGHT / 2)), 48, 48};

  e->speed = 3.5;
  e->healthBar = 1;
  e->health = 1;
  e->graphicHealth = 1;

  for (i = 0; i < PARTICLENUM; i++) {
    e->particles[i].speed = (Vector2){0, 0};
    e->particles[i].c = WHITE;
    e->particles[i].dim = 0;
    e->particles[i].pos = (Vector2){-WIDTH, -HEIGHT};
  }

  e->active = false;
  e->isStray = false;
}

int resetEnemy(Enemy *e, int score) {
  int w, ret = 0;

  setParticles(e->particles, GOLD, PURPLE, GOLD, FULL);
  startParticles(e->particles,
                 (Vector2){e->hitbox.x + e->hitbox.width / 2.0,
                           e->hitbox.y + e->hitbox.height / 2.0},
                 &e->active);

  if (score % 4 == 0 && rand() % 2 == 0)
    e->type++;

  if (e->isStray) {
    e->speed /= 5;
  }

  switch (e->type) {
  case 1:
    w = 48;
    break;
  case 2:
    w = 64;
    break;
  case 3:
    w = 80;
    break;
  case 4:
    w = 96;
    break;
  case 5:
    ret = 1;
    w = 48;
    e->type = 1;
    break;
  }

  e->healthBar = e->type;
  e->health = e->type;
  e->graphicHealth = e->health;

  e->hitbox = (Rectangle){
      (float)(rand() % (WIDTH - w)),
      (-1 * (float)(rand() % (HEIGHT / 2))) - (int)(HEIGHT / 3), w, w};

  if (score <= 900)
    w = rand() % (6 - score / 300); // im using w as reciling
  else
    w = rand() % 3;

  if (w == 1) {
    e->isStray = true;
    e->speed *= 5;
    e->hitbox.y -= (WIDTH * 3.0 / 4.0);
  } else {
    e->isStray = false;
  }

  return ret;
}

void setEnemies(Enemies *es) {
  int i;

  es->num = 2;

  es->enemies = realloc(es->enemies, sizeof(Enemy) * es->num);

  for (i = 0; i < es->num; i++) {
    setEnemy(&es->enemies[i]);
  }
}

void addEnemies(Enemies *es) {
  assert(es != NULL);
  es->num++;

  es->enemies = realloc(es->enemies, sizeof(Enemy) * es->num);

  setEnemy(&es->enemies[es->num - 1]);
}

void removeEnemies(Enemies *es) {
  assert(es != NULL && es->enemies != NULL);
  es->num--;

  es->enemies = realloc(es->enemies, sizeof(Enemy) * es->num);
}

void freeEnemies(Enemies *es) {
  if (es->enemies == NULL || es == NULL)
    return;

  free(es->enemies);
}

void manageEnemies(Enemies *es) {
  int i;

  for (i = 0; i < es->num; i++) {
    es->enemies[i].hitbox.y += DELTA * es->enemies[i].speed;
    manageParticles(es->enemies[i].particles, es->enemies[i].type,
                    &es->enemies[i].active);
  }
}

void renderEnemies(Enemies *es) {
  int i;

  for (i = 0; i < es->num; i++) {
    DrawRectangleRounded(es->enemies[i].hitbox, 0.25, 10, LIGHTGRAY);

    DrawRectangle(es->enemies[i].hitbox.x + es->enemies[i].hitbox.width / 2.0 -
                      48,
                  es->enemies[i].hitbox.y - 24, 96, 8, RED);
    DrawRectangle(
        es->enemies[i].hitbox.x + es->enemies[i].hitbox.width / 2.0 - 48,
        es->enemies[i].hitbox.y - 24,
        96 * es->enemies[i].graphicHealth / es->enemies[i].healthBar, 8, GREEN);

    renderParticles(es->enemies[i].particles, &es->enemies[i].active);

    if (es->enemies[i].graphicHealth > es->enemies[i].health) {
      es->enemies[i].graphicHealth -= DELTA / 6;
    }
  }
}
