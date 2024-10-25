#ifndef DEFINES_H
#define DEFINES_H

#ifdef WINDOWS_H
#define FULLSCREEN ToggleFullscreen()
#else
#define FULLSCREEN
#endif

#define WIDTH 1920
#define HEIGHT 1080

#define DELTA GetFrameTime() * 50

#define BACKGROUND "images/b2.png"
#define WARNING "images/warning.png"

#define TITLEFONT "fonts/Wolfskin.ttf"
#define NORMALFONT TITLEFONT

#define TITLESIZE 256
#define NORMALSIZE 64

#define PARTICLENUM 50

typedef enum { MENU = 0, GAME, PAUSE, GAMEOVER, SHOP, QUIT } GameState;
typedef enum { FULL = 0, BOTTOM, TOP, LEFT, RIGHT } ParticleType;

#endif
