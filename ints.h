#include <SDL/SDL.h>
#include <cstdlib>
#include <ctime>

//Game State
int state(0);

//Countdown
int countDown(120);

//Screen Dimensions
int sWidth(400),sHeight(400),sBits(32);

//Sprite Dimensions
int srcX(0),srcY(0),dstX(0),dstY(0),width(38),height(40);

//Item Dimensions
int insX(100),insY(100),insWidth(30),insHeight(29);

//time bar
Uint32 colour;
double timeWidth(150);
//int timeRemaining(900);


//Item Logic
bool collected = false;
//bool bottles[5] = {false};
int quantity(0);

//Direction Logic
int U(0),D(0),L(0),R(0);

//Frame Rate
const int FPS = 30;
Uint32 start;

//Keyboard Logic
bool keys[323] = {false};

//Surfaces
SDL_Surface *screen, *background, *kyle, *insulin, *text, *startButton, *exitButton, *titleScreen, *winScreen;
SDL_Surface *countDownSurface, *timeTitle, *timeBar, *bottlesLeft, *loseScreen;

//Rectangles
SDL_Rect kyleRect, insulinRect, textRect, startRect, exitRect, bottlesCrop, kyleCrop, countDownCrop;
