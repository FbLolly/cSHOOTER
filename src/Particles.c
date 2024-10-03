#include "headers/Particles.h"
#include "headers/defines.h"
#include <raylib.h>
#include <stdlib.h>

void setParticles(Particle p[], Color c1, Color c2, Color c3,
                  ParticleType particleType) {
  int i;
  int a;

  for (i = 0; i < PARTICLENUM; i++) {
    p[i].dim = (rand() % 20) + 2;

    a = rand() % 3;
    if (a == 0)
      p[i].c = c1;
    else if (a == 1)
      p[i].c = c2;
    else if (a == 2)
      p[i].c = c3;

    switch (particleType) {
    case FULL:
      p[i].speed =
          (Vector2){((rand() % 16) - 8) / 4.0, ((rand() % 16) - 8) / 4.0};
      break;
    case BOTTOM:
      p[i].speed =
          (Vector2){((rand() % 16) - 8) / 4.0, ((rand() % 8) + 1) / 4.0};
      break;
    case TOP:
      p[i].speed =
          (Vector2){((rand() % 16) - 8) / 4.0, ((rand() % 8) + 1) / -4.0};
      break;
    default:
      break;
    }
  }
}

void startParticles(Particle p[], Vector2 pos) {
  int i;

  for (i = 0; i < PARTICLENUM; i++) {
    p[i].pos = (Vector2){pos.x - p[i].dim / 2, pos.y - p[i].dim / 2};
  }
}

void manageParticles(Particle p[], int type) {
  int i;

  for (i = 0; i < PARTICLENUM; i++) {
    p[i].pos.x += p[i].speed.x * DELTA * 5;
    p[i].pos.y += p[i].speed.y * DELTA * 5;

    if (rand() % 2 == 0 && p[i].dim >= DELTA * 2 * (1.0 / type))
      p[i].dim -= DELTA * 2 * (0.8 / type);
  }
}

void renderParticles(Particle p[]) {
  int i;

  for (i = 0; i < PARTICLENUM; i++) {
    DrawRectangle(p[i].pos.x, p[i].pos.y, p[i].dim, p[i].dim, p[i].c);
  }
}
