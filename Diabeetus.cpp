#include "Diabeetus.h"
#include <ctime>

Diabeetus::Diabeetus() {

}

void Diabeetus::Init() {
	done = false;
	sWidth = 400;
	sHeight = 400;
	sBits = 32;

	for (int i = 0; i < 323; i++)
	{
		keys[i] = false;
	}

	quantity = 0;
	countDown = 120;

	state = 0;
	collected = false;
	timeWidth = 150;

	SDL_Init(SDL_INIT_VIDEO);
	screen = SDL_SetVideoMode(sWidth, sHeight + 40, sBits, SDL_SWSURFACE);
	titleScreen = SDL_LoadBMP("graphics/title.bmp");
	startButton = SDL_LoadBMP("graphics/start.bmp");
	exitButton = SDL_LoadBMP("graphics/exit.bmp");
	background = SDL_LoadBMP("graphics/background.bmp");
	kyle = SDL_LoadBMP("graphics/kyle.bmp");
	insulin = SDL_LoadBMP("graphics/insulin.bmp");
	SDL_SetColorKey(insulin, SDL_SRCCOLORKEY, SDL_MapRGB(insulin->format, 1, 249, 0));
	winScreen = SDL_LoadBMP("graphics/win.bmp");
	loseScreen = SDL_LoadBMP("graphics/lose.bmp");
	countDownSurface = SDL_LoadBMP("graphics/countdown.bmp");
	timeTitle = SDL_LoadBMP("graphics/time.bmp");
	timeBar = SDL_LoadBMP("graphics/timeBar.bmp");
	bottlesLeft = SDL_LoadBMP("graphics/bottles.bmp");
	SDL_WM_SetCaption("Diabeetus", NULL);

	dstX = 0;
	dstY = 0;
	width = 38;
	height = 40;

	insX = 100;
	insY = 100;
	insWidth = 30;
	insHeight = 29;

	U = 0;
	D = 0;
	L = 0;
	R = 0;

	startRect = gameSetRect(140, 125, 100, 50);
	exitRect = gameSetRect(140, 225, 100, 50);

	countDownCrop = gameSetRect(390, 0, 130, 100);
	bottlesCrop = gameSetRect(0, 120, 168, 30);
	kyleCrop = gameSetRect(0, 0, 40, 40);

	colour = SDL_MapRGB(screen->format, 255, 255, 255);

	srand(time(0));
	insX = rand() % (sWidth - insWidth);
	insY = rand() % (sHeight - insHeight);
	if ((insX >= dstX&&insX <= dstX + width) && (insY >= dstY&&insY <= dstY + height)) {
		while ((insX >= dstX&&insX <= dstX + width) && (insY >= dstY&&insY <= dstY + height))insY = rand() % (sHeight - insHeight);
	}

}

SDL_Rect Diabeetus::gameSetRect(int x, int y, int w, int h) {
	SDL_Rect r;
	r.x = x;
	r.y = y;
	r.w = w;
	r.h = h;
	return r;
}

void Diabeetus::Input() {
	//All States
	start = SDL_GetTicks();
	SDL_Event event;
	if (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) done = true;
		if (event.type == SDL_KEYDOWN)keys[event.key.keysym.sym] = true;
		if (event.type == SDL_KEYUP)keys[event.key.keysym.sym] = false;
	}
	if (keys[SDLK_ESCAPE])done = true;
	if (!state) {
		//Main Menu State (state == 0)
		if (event.type == SDL_MOUSEBUTTONDOWN) {
			int x = event.button.x;
			int y = event.button.y;
			if (x > startRect.x && x<startRect.x + startRect.w && y>startRect.y && y < startRect.y + startRect.h) {
				state = 1;
			}
			else if (x > exitRect.x && x<exitRect.x + exitRect.w && y>exitRect.y && y < exitRect.y + exitRect.h) {
				done = true;
			}
		}
	}
	else if (state == 1) {
		//Play State (state == 1)
		if (countDown) {
			countDown--;
		}
		else {
			timeWidth -= .25;
			if (!timeWidth) state = 3;
			if (quantity == 10) state = 2;
			if (keys[SDLK_DOWN]) {
				if (D < 5) {
					if (!keys[SDLK_LEFT] && !keys[SDLK_RIGHT]) {
						kyleCrop.x = 0;
						kyleCrop.y = 0;
					}
					D++;
				}
				else if (D < 10) {
					if (!keys[SDLK_LEFT] && !keys[SDLK_RIGHT]) {
						kyleCrop.x = 40;
						kyleCrop.y = 0;
					}
					D++;
				}
				else D = 0;
				dstY += 2;
			}
			if (keys[SDLK_RIGHT]) {
				if (R < 5) {
					kyleCrop.x = 80;
					kyleCrop.y = 40;
					R++;
				}
				else if (R < 10) {
					kyleCrop.x = 120;
					kyleCrop.y = 40;
					R++;
				}
				else R = 0;
				dstX += 2;
			}
			if (keys[SDLK_UP]) {
				if (U < 5) {
					if (!keys[SDLK_LEFT] && !keys[SDLK_RIGHT]) {
						kyleCrop.x = 80;
						kyleCrop.y = 0;
					}
					U++;
				}
				else if (U < 10) {
					if (!keys[SDLK_LEFT] && !keys[SDLK_RIGHT]) {
						kyleCrop.x = 120;
						kyleCrop.y = 0;
					}
					U++;
				}
				else U = 0;
				dstY -= 2;
			}
			if (keys[SDLK_LEFT]) {
				if (L < 5) {
					kyleCrop.x = 0;
					kyleCrop.y = 40;
					L++;
				}
				else if (L < 10) {
					kyleCrop.x = 40;
					kyleCrop.y = 40;
					L++;
				}
				else L = 0;
				dstX -= 2;
			}
			//Collision Detection
			if (dstX < 0)dstX = 0;
			if (dstY < 0)dstY = 0;
			if (dstX + width > 400) dstX = 400 - width;
			if (dstY + height > 400) dstY = 400 - height;
			if (collision(&kyleRect, &insulinRect)) {
				collected = true;
			}
			if (collected) {
				quantity++;
				insX = rand() % (sWidth - insWidth);
				insY = rand() % (sHeight - insHeight);
				if ((insX >= dstX&&insX <= dstX + width) && (insY >= dstY&&insY <= dstY + height)) {
					// if the new insulin's screen coordinates would overlap kyle's coordinates,
					// recalculate a new insulin location
					while ((insX >= dstX&&insX <= dstX + width) && (insY >= dstY&&insY <= dstY + height))
						insY = rand() % (sHeight - insHeight);
				}
				quantity++;
				collected = false;
			}
		}
	}
	else if (state == 2 || state == 3) {
		if (keys[SDLK_RETURN]) {
			countDown = 120;
			timeWidth = 150;
			quantity = 0;
			dstX = 0;
			dstY = 0;
			kyleCrop.x = 0;
			kyleCrop.y = 0;
			bottlesCrop.y = 120;
			state = 0;
		}
	}
}

void Diabeetus::Update() {
	SDL_Flip(screen);
	if (1000 / FPS > SDL_GetTicks() - start) {
		SDL_Delay(1000 / FPS - (SDL_GetTicks() - start));
	}
}

void Diabeetus::Clean() {
	SDL_FreeSurface(titleScreen);
	SDL_FreeSurface(startButton);
	SDL_FreeSurface(exitButton);

	SDL_FreeSurface(kyle);
	SDL_FreeSurface(bottlesLeft);
	SDL_FreeSurface(countDownSurface);
	SDL_FreeSurface(timeTitle);
	SDL_FreeSurface(timeBar);
	SDL_FreeSurface(loseScreen);
	SDL_FreeSurface(winScreen);
	SDL_FreeSurface(screen);

	SDL_Quit();
	exit(0);
}

bool Diabeetus::Done() {
	return done;
}

bool Diabeetus::collision(SDL_Rect *rect1, SDL_Rect *rect2) {
	if (rect1->y + 2 >= rect2->y + rect2->h) return false;  //bottom of target
	if (rect1->x + 20 >= rect2->x + rect2->w) return false; //right of target
	if (rect1->y + rect1->h <= rect2->y + 5) return false;  //top of target
	if (rect1->x + rect1->w <= rect2->x + 20) return false; //left of target
	return true;
}

void Diabeetus::Render() {
	//Main Menu State (state == 0)
	if (!state) {
		drawBackground(0, 0, titleScreen, NULL, screen);
		drawBackground(140, 125, startButton, NULL, screen);
		drawBackground(140, 225, exitButton, NULL, screen);
	}
	else if (state == 1) {

		//Play State (state == 1)
		kyleRect = gameSetRect(dstX, dstY, width, height);
		insulinRect = gameSetRect(insX, insY, insWidth, insHeight);
		drawBackground(0, 0, background, NULL, screen);
		drawBackground(190, 400, timeTitle, NULL, screen);
		if (quantity == 2) {
			bottlesCrop.y = 90;
		}
		else if (quantity == 4) {
			bottlesCrop.y = 60;
		}
		else if (quantity == 6) {
			bottlesCrop.y = 30;
		}
		else if (quantity == 8) {
			bottlesCrop.y = 0;
		}
		drawBackground(10, 405, bottlesLeft, &bottlesCrop, screen);
		drawRect(238, 412, timeWidth, 15, colour);
		if (countDown > 90) {
			countDownCrop.x = 390;
			drawBackground(135, 140, countDownSurface, &countDownCrop, screen);
		}
		else if (countDown > 60) {
			countDownCrop.x = 260;
			drawBackground(135, 140, countDownSurface, &countDownCrop, screen);
		}
		else if (countDown > 30) {
			countDownCrop.x = 130;
			drawBackground(135, 140, countDownSurface, &countDownCrop, screen);
		}
		else if (countDown > 0) {
			countDownCrop.x = 0;
			drawBackground(135, 140, countDownSurface, &countDownCrop, screen);
		}
		if (!countDown) {
			drawInsulin(insX, insY, insulin, screen);
		}
		SDL_SetColorKey(kyle, SDL_SRCCOLORKEY, SDL_MapRGB(kyle->format, 1, 249, 0));
		drawSprite(dstX, dstY, width, height, kyle, &kyleCrop, screen);
	}
	else if (state == 2) {
		//Win State (state == 2)
		drawBackground(0, 0, winScreen, NULL, screen);
	}
	else if (state == 3) {
		//Lose State (state == 3)
		drawBackground(0, 0, loseScreen, NULL, screen);
	}
}

void Diabeetus::drawBackground(int x, int y, SDL_Surface *source, SDL_Rect *crop, SDL_Surface *destination) {
	SDL_Rect rect;
	rect.x = x;
	rect.y = y;
	SDL_BlitSurface(source, crop, destination, &rect);
}

void Diabeetus::drawInsulin(int x, int y, SDL_Surface *source, SDL_Surface *destination) {
	if (!collected && quantity < 10) {
		SDL_Rect rect;
		rect.x = x;
		rect.y = y;
		rect.w = insWidth;
		rect.h = insHeight;
		SDL_BlitSurface(source, NULL, destination, &rect);
	}
}

void Diabeetus::drawSprite(int x, int y, int w, int h, SDL_Surface *source, SDL_Rect *crop, SDL_Surface *destination) {

	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	dst.w = w;
	dst.h = h;
	SDL_BlitSurface(source, crop, destination, &dst);
}

void Diabeetus::drawRect(double x, double y, double w, double h, Uint32 colour) {
	SDL_Rect rect;
	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;
	SDL_FillRect(screen, &rect, colour);
}
