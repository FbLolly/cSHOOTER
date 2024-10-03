#ifndef PARTICLES_H
#define PARTICLES_H

#include "defines.h"
#include <raylib.h>

typedef struct {
  Vector2 pos;
  float dim;

  Vector2 speed;
  Color c;
} Particle;

void setParticles(Particle p[], Color c1, Color c2, Color c3,
                  ParticleType particleType);
void startParticles(Particle p[], Vector2 pos);
void manageParticles(Particle p[], int type);
void renderParticles(Particle p[]);

#endif
