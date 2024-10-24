#ifndef ENEMY_H
#define ENEMY_H

#include "Particles.h"
#include "defines.h"
#include <raylib.h>
#include <stdlib.h>

typedef struct {
  Rectangle hitbox;

  int type;

  int healthBar;
  int health;
  float graphicHealth;

  float speed;
  Particle particles[PARTICLENUM];

  bool active;
  bool isStray;
} Enemy;

typedef struct {
  Enemy *enemies;

  int num;
} Enemies;

void setEnemy(Enemy *e);
int resetEnemy(Enemy *e, int score); // returns 0 if everything went well,
                                     // returns 1 if we have to add an enemy

void setEnemies(Enemies *es);
void manageEnemies(Enemies *es);
void addEnemies(Enemies *es);
void removeEnemies(Enemies *es);
void freeEnemies(Enemies *es);
void renderEnemies(Enemies *es);

#endif
