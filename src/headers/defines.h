#ifndef DEFINES_H
#define DEFINES_H

#define WIDTH 1920
#define HEIGHT 1080

#define DELTA GetFrameTime() * 50

#define TITLEFONT "fonts/Wolfskin.ttf"
#define NORMALFONT TITLEFONT

#define TITLESIZE 256
#define NORMALSIZE 64

#define PARTICLENUM 50

typedef enum { MENU = 0, GAME, GAMEOVER, SHOP, QUIT } GameState;
typedef enum { FULL = 0, BOTTOM, TOP, LEFT, RIGHT } ParticleType;

#endif
