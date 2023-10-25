#include "Diabeetus.h"
#include <iostream>
#include <ctime>
#include <limits>

Diabeetus::Diabeetus() {

}

inline int Diabeetus::nextInsX()
{
	return rand() % (sWidth - insWidth);
}

inline int Diabeetus::nextInsY()
{
	return rand() % ((sHeight - 41) - insHeight);
}

void Diabeetus::init() {

	done = false;

	dstX = 0;
	dstY = 0;
	width = 40;
	height = 40;

	insX = 100;
	insY = 100;
	insWidth = 30;
	insHeight = 29;

	sWidth = 400;
	sHeight = 440;
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

	U = 0;
	D = 0;
	L = 0;
	R = 0;

	FPS = 30;

	if (SDL_Init(SDL_INIT_VIDEO))
	{
		std::cout << "failed to initialize SDL" << std::endl;
        return;
	}

	win = SDL_CreateWindow(
        "Diabeetus",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        sWidth,
        sHeight,
        SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI);
    if (win == NULL)
    {
		std::cout << "failed to create window" << std::endl;
        return;
    }

	ren = SDL_CreateRenderer(
        win,
        -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (ren == NULL)
    {
        SDL_DestroyWindow(win);
		std::cout << "failed to create renderer" << std::endl;
        return;
    }

	int scale = 1;
	int ww, wh;
    int rw, rh;
    SDL_GetWindowSize(win, &ww, &wh);
    SDL_GetRendererOutputSize(ren, &rw, &rh);
    if (rw > ww)
    {
        int scale_correction_x = rw / ww;
        int scale_correction_y = rh / wh;
        SDL_RenderSetScale(ren, (float)scale_correction_x * scale, (float)scale_correction_y * scale);
    }
    else if (scale > 0)
    {
        SDL_RenderSetScale(ren, (float)scale, (float)scale);
    }

	SDL_Surface *backgroundSurface = SDL_LoadBMP("graphics/background.bmp");
	SDL_Surface *kyleSurface = SDL_LoadBMP("graphics/kyle.bmp");
	SDL_Surface *insulinSurface = SDL_LoadBMP("graphics/insulin.bmp");
	SDL_Surface *startButtonSurface = SDL_LoadBMP("graphics/start.bmp");
	SDL_Surface *exitButtonSurface = SDL_LoadBMP("graphics/exit.bmp");
	SDL_Surface *titleScreenSurface = SDL_LoadBMP("graphics/title.bmp");
	SDL_Surface *winScreenSurface = SDL_LoadBMP("graphics/win.bmp");
	SDL_Surface *countDownSurface = SDL_LoadBMP("graphics/countdown.bmp");
	SDL_Surface *timeTitleSurface = SDL_LoadBMP("graphics/time.bmp");
	SDL_Surface *timeBarSurface = SDL_LoadBMP("graphics/timeBar.bmp");
	SDL_Surface *bottlesLeftSurface = SDL_LoadBMP("graphics/bottles.bmp");
	SDL_Surface *loseScreenSurface = SDL_LoadBMP("graphics/lose.bmp");

	SDL_SetColorKey(kyleSurface, SDL_TRUE, SDL_MapRGB(kyleSurface->format, 1, 249, 0));
	SDL_SetColorKey(insulinSurface, SDL_TRUE, SDL_MapRGB(insulinSurface->format, 1, 249, 0));

	backgroundTexture = SDL_CreateTextureFromSurface(ren, backgroundSurface);
	kyleTexture = SDL_CreateTextureFromSurface(ren, kyleSurface);
	insulinTexture = SDL_CreateTextureFromSurface(ren, insulinSurface);
	startButtonTexture = SDL_CreateTextureFromSurface(ren, startButtonSurface);
	exitButtonTexture = SDL_CreateTextureFromSurface(ren, exitButtonSurface);
	titleScreenTexture = SDL_CreateTextureFromSurface(ren, titleScreenSurface);
	winScreenTexture = SDL_CreateTextureFromSurface(ren, winScreenSurface);
	countDownTexture = SDL_CreateTextureFromSurface(ren, countDownSurface);
	timeTitleTexture = SDL_CreateTextureFromSurface(ren, timeTitleSurface);
	timeBarTexture = SDL_CreateTextureFromSurface(ren, timeBarSurface);
	bottlesLeftTexture = SDL_CreateTextureFromSurface(ren, bottlesLeftSurface);
	loseScreenTexture = SDL_CreateTextureFromSurface(ren, loseScreenSurface);

	SDL_FreeSurface(backgroundSurface);
	SDL_FreeSurface(kyleSurface);
	SDL_FreeSurface(insulinSurface);
	SDL_FreeSurface(startButtonSurface);
	SDL_FreeSurface(exitButtonSurface);
	SDL_FreeSurface(titleScreenSurface);
	SDL_FreeSurface(winScreenSurface);
	SDL_FreeSurface(countDownSurface);
	SDL_FreeSurface(timeTitleSurface);
	SDL_FreeSurface(timeBarSurface);
	SDL_FreeSurface(bottlesLeftSurface);
	SDL_FreeSurface(loseScreenSurface);

	startRect = setRect(140, 125, 100, 50);
	exitRect = setRect(140, 225, 100, 50);
	countDownCrop = setRect(390, 0, 130, 100);
	bottlesCrop = setRect(0, 120, 168, 30);
	kyleCrop = setRect(0, 0, 40, 40);

	colour = 0xFFFFFFFF;

	srand((unsigned int)(time(0) & INT_MAX));
	insX = nextInsX();
	insY = nextInsY();
	if ((insX >= dstX&&insX <= dstX + width) && (insY >= dstY&&insY <= dstY + height)) {
		while ((insX >= dstX&&insX <= dstX + width) && (insY >= dstY&&insY <= dstY + height))
			insY = nextInsY();
	}
}

SDL_Rect Diabeetus::setRect(int x, int y, int w, int h) {
	SDL_Rect r;
	r.x = x;
	r.y = y;
	r.w = w;
	r.h = h;
	return r;
}

void Diabeetus::input() {
	//All States
	start = SDL_GetTicks64();
	SDL_Event event;
	if (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) done = true;
		if (event.type == SDL_KEYDOWN)keys[event.key.keysym.scancode] = true;
		if (event.type == SDL_KEYUP)keys[event.key.keysym.scancode] = false;
	}
	if (keys[SDL_SCANCODE_ESCAPE])done = true;
	if (!state) {
		// main menu
		if (event.type == SDL_MOUSEBUTTONDOWN) {
			int x = event.button.x;
			int y = event.button.y;
			if (x > startRect.x && x < startRect.x + startRect.w && y > startRect.y && y < startRect.y + startRect.h) {
				state = 1;
			}
			else if (x > exitRect.x && x < exitRect.x + exitRect.w && y > exitRect.y && y < exitRect.y + exitRect.h) {
				done = true;
			}
		}
	}
	else if (state == 1) {
		// primary gameplay
		if (countDown) {
			countDown--;
		}
		else {
			timeWidth -= .25;
			if (!timeWidth) state = 3;
			if (quantity == 10) state = 2;
			if (keys[SDL_SCANCODE_DOWN]) {
				if (D < 5) {
					if (!keys[SDL_SCANCODE_LEFT] && !keys[SDL_SCANCODE_RIGHT]) {
						kyleCrop.x = 0;
						kyleCrop.y = 0;
					}
					D++;
				}
				else if (D < 10) {
					if (!keys[SDL_SCANCODE_LEFT] && !keys[SDL_SCANCODE_RIGHT]) {
						kyleCrop.x = 40;
						kyleCrop.y = 0;
					}
					D++;
				}
				else D = 0;
				dstY += 2;
			}
			if (keys[SDL_SCANCODE_RIGHT]) {
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
			if (keys[SDL_SCANCODE_UP]) {
				if (U < 5) {
					if (!keys[SDL_SCANCODE_LEFT] && !keys[SDL_SCANCODE_RIGHT]) {
						kyleCrop.x = 80;
						kyleCrop.y = 0;
					}
					U++;
				}
				else if (U < 10) {
					if (!keys[SDL_SCANCODE_LEFT] && !keys[SDL_SCANCODE_RIGHT]) {
						kyleCrop.x = 120;
						kyleCrop.y = 0;
					}
					U++;
				}
				else U = 0;
				dstY -= 2;
			}
			if (keys[SDL_SCANCODE_LEFT]) {
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
			// collision detection
			if (dstX < 0)dstX = 0;
			if (dstY < 0)dstY = 0;
			if (dstX + width > 400) dstX = 400 - width;
			if (dstY + height > 400) dstY = 400 - height;
			if (collision(&kyleRect, &insulinRect)) {
				collected = true;
			}
			if (collected) {
				quantity++;
				insX = nextInsX();
				insY = nextInsY();
				if ((insX >= dstX&&insX <= dstX + width) && (insY >= dstY&&insY <= dstY + height)) {
					// If the new insulin's screen coordinates would overlap kyle's coordinates,
					// recalculate a new insulin location.
					while ((insX >= dstX&&insX <= dstX + width) && (insY >= dstY&&insY <= dstY + height))
						insY = nextInsY();
				}
				quantity++;
				collected = false;
			}
		}
	}
	else if (state == 2 || state == 3) {
		if (keys[SDL_SCANCODE_RETURN]) {
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

void Diabeetus::update() {
	if (1000 / FPS > SDL_GetTicks64() - start) {
		SDL_Delay(Uint32(1000 / FPS - (SDL_GetTicks64() - start)));
	}
}

void Diabeetus::clean() {

	SDL_DestroyTexture(backgroundTexture);
	SDL_DestroyTexture(kyleTexture);
	SDL_DestroyTexture(insulinTexture);
	SDL_DestroyTexture(startButtonTexture);
	SDL_DestroyTexture(exitButtonTexture);
	SDL_DestroyTexture(titleScreenTexture);
	SDL_DestroyTexture(winScreenTexture);
	SDL_DestroyTexture(countDownTexture);
	SDL_DestroyTexture(timeTitleTexture);
	SDL_DestroyTexture(timeBarTexture);
	SDL_DestroyTexture(bottlesLeftTexture);
	SDL_DestroyTexture(loseScreenTexture);

	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);

	SDL_Quit();
	exit(0);
}

bool Diabeetus::isDone() {
	return done;
}

bool Diabeetus::collision(SDL_Rect *rect1, SDL_Rect *rect2) {
	if (rect1->y + 2 >= rect2->y + rect2->h) return false;  // bottom of target
	if (rect1->x + 20 >= rect2->x + rect2->w) return false; // right of target
	if (rect1->y + rect1->h <= rect2->y + 5) return false;  // top of target
	if (rect1->x + rect1->w <= rect2->x + 20) return false; // left of target
	return true;
}

void Diabeetus::render() {

	SDL_SetRenderDrawColor(ren, 20, 20, 20, 255);
    SDL_RenderClear(ren);

	// main menu
	if (!state) {
		drawRect(0, 0, 0, 0, titleScreenTexture, NULL);
		drawRect(140, 125, 0, 0, startButtonTexture, NULL);
		drawRect(140, 225, 0, 0, exitButtonTexture, NULL);
	}
	else if (state == 1) {
		// primary gameplay
		kyleRect = setRect(dstX, dstY, width, height);
		insulinRect = setRect(insX, insY, insWidth, insHeight);
		drawRect(0, 0, 0, 0, backgroundTexture, NULL);
		drawRect(190, 400, 0, 0, timeTitleTexture, NULL);
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
		drawRect(10, 405, 0, 0, bottlesLeftTexture, &bottlesCrop);
		fillRect(238, 412, timeWidth, 15, colour);
		if (countDown > 90) {
			countDownCrop.x = 390;
			drawRect(135, 140, 0, 0, countDownTexture, &countDownCrop);
		}
		else if (countDown > 60) {
			countDownCrop.x = 260;
			drawRect(135, 140, 0, 0, countDownTexture, &countDownCrop);
		}
		else if (countDown > 30) {
			countDownCrop.x = 130;
			drawRect(135, 140, 0, 0, countDownTexture, &countDownCrop);
		}
		else if (countDown > 0) {
			countDownCrop.x = 0;
			drawRect(135, 140, 0, 0, countDownTexture, &countDownCrop);
		}
		if (!countDown) {
			drawRect(insX, insY, insWidth, insHeight, insulinTexture, NULL);
		}
		drawRect(dstX, dstY, width, height, kyleTexture, &kyleCrop);
	}
	else if (state == 2) {
		// win screen
		drawRect(0, 0, 0, 0, winScreenTexture, NULL);
	}
	else if (state == 3) {
		// lose screen
		drawRect(0, 0, 0, 0, loseScreenTexture, NULL);
	}

	SDL_RenderPresent(ren);
}

void Diabeetus::drawRect(int x, int y, int w, int h, SDL_Texture *texture, SDL_Rect *crop) {

	int qWidth, qHeight;
	if (SDL_QueryTexture(texture, NULL, NULL, &qWidth, &qHeight))
	{
		return;
	}

	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	dst.w = w ? w : crop != NULL ? crop->w : qWidth;
	dst.h = h ? h : crop != NULL ? crop->h : qHeight;

	SDL_RenderCopy(ren, texture, crop, &dst);
}

void Diabeetus::fillRect(double x, double y, double w, double h, Uint32 colour) {
	SDL_Rect rect;
	rect.x = (int)x;
	rect.y = (int)y;
	rect.w = (int)w;
	rect.h = (int)h;

	// Here, we expect colour to be in the format AARRGGBB.
	SDL_SetRenderDrawColor(
		ren,
		(colour & (0xFF << 16)) >> 16, // red
		(colour & (0xFF << 8)) >> 8,   // green
		(colour & (0xFF)),             // blue
		(colour & (0xFF << 24)) >> 24  // alpha
	);
	SDL_RenderFillRect(ren, &rect);
}
