#include "gameEvents.h"
#include "ints.h"

gameEvents::gameEvents(){

}

void gameEvents::gameInit(){
    done = false;
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    screen = SDL_SetVideoMode(sWidth,sHeight+40,sBits,SDL_SWSURFACE);
    titleScreen = SDL_LoadBMP("graphics/title.bmp");
    startButton = SDL_LoadBMP("graphics/start.bmp");
    exitButton = SDL_LoadBMP("graphics/exit.bmp");
    background = SDL_LoadBMP("graphics/background.bmp");
    kyle = SDL_LoadBMP("graphics/kyleFront1.bmp");
    insulin = SDL_LoadBMP("graphics/insulin.bmp");
    SDL_SetColorKey(insulin,SDL_SRCCOLORKEY,SDL_MapRGB(insulin->format,1,249,0));
    winScreen = SDL_LoadBMP("graphics/win.bmp");
    loseScreen = SDL_LoadBMP("graphics/lose.bmp");
    one = SDL_LoadBMP("graphics/one.bmp");
    two = SDL_LoadBMP("graphics/two.bmp");
    three = SDL_LoadBMP("graphics/three.bmp");
    GO = SDL_LoadBMP("graphics/go.bmp");
    timeTitle = SDL_LoadBMP("graphics/time.bmp");
    timeBar = SDL_LoadBMP("graphics/timeBar.bmp");
    bottlesLeft = SDL_LoadBMP("graphics/bottles5.bmp");
    SDL_WM_SetCaption("Diabeetus",NULL);

    startRect = gameSetRects(140,125,100,50);
    exitRect = gameSetRects(140,225,100,50);

    colour = SDL_MapRGB(screen->format,255,255,255);

    srand(time(0));
    insX = rand()%(sWidth-insWidth);
    insY = rand()%(sHeight-insHeight);
    if((insX>=dstX&&insX<=dstX+width)&&(insY>=dstY&&insY<=dstY+height)){
        while((insX>=dstX&&insX<=dstX+width)&&(insY>=dstY&&insY<=dstY+height))insY = rand()%(sHeight-insHeight);
    }

}

SDL_Rect gameEvents::gameSetRects(int x,int y,int w,int h){
    SDL_Rect r;
    r.x = x;
    r.y = y;
    r.w = w;
    r.h = h;
    return r;
}

void gameEvents::gameInput(){
    //All States
    start = SDL_GetTicks();
    SDL_Event event;
    if(SDL_PollEvent(&event)){
        if(event.type==SDL_QUIT) done = true;
        if(event.type==SDL_KEYDOWN)keys[event.key.keysym.sym] = true;
        if(event.type==SDL_KEYUP)keys[event.key.keysym.sym] = false;
    }
    if(keys[SDLK_ESCAPE])done = true;
    if(!state){
        //Main Menu State (state == 0)
        if(event.type==SDL_MOUSEBUTTONDOWN){
            int x = event.button.x;
            int y = event.button.y;
            if(x>startRect.x && x<startRect.x+startRect.w && y>startRect.y && y<startRect.y+startRect.h){
                state = 1;
            }else if(x>exitRect.x && x<exitRect.x+exitRect.w && y>exitRect.y && y<exitRect.y+exitRect.h){
                done = true;
            }
        }
    }else if(state==1){
    //Play State (state == 1)
    if(countDown){
        countDown--;
    }else{
    timeWidth-=.25;
    if(!timeWidth)state = 3;
    if(quantity==10)state = 2;
    if(keys[SDLK_DOWN]){
        if(D<5){
            if(!keys[SDLK_LEFT]&&!keys[SDLK_RIGHT])kyle = SDL_LoadBMP("graphics/kyleFront1.bmp");
            D++;
        }else if(D<10){
            if(!keys[SDLK_LEFT]&&!keys[SDLK_RIGHT])kyle = SDL_LoadBMP("graphics/kyleFront2.bmp");
            D++;
        }else D = 0;
        dstY+=2;
    }
    if(keys[SDLK_RIGHT]){
        if(R<5){
            kyle = SDL_LoadBMP("graphics/kyleRight1.bmp");
            R++;
        }else if(R<10){
            kyle = SDL_LoadBMP("graphics/kyleRight2.bmp");
            R++;
        }else R = 0;
        dstX+=2;
    }
    if(keys[SDLK_UP]){
        if(U<5){
            if(!keys[SDLK_LEFT]&&!keys[SDLK_RIGHT])kyle = SDL_LoadBMP("graphics/kyleBack1.bmp");
            U++;
        }else if(U<10){
            if(!keys[SDLK_LEFT]&&!keys[SDLK_RIGHT])kyle = SDL_LoadBMP("graphics/kyleBack2.bmp");
            U++;
        }else U = 0;
        dstY-=2;
    }
    if(keys[SDLK_LEFT]){
        if(L<5){
            kyle = SDL_LoadBMP("graphics/kyleLeft1.bmp");
            L++;
        }else if(L<10){
            kyle = SDL_LoadBMP("graphics/kyleLeft2.bmp");
            L++;
        }else L = 0;
        dstX-=2;
    }
    //Collision Detection
    if(dstX<0)dstX=0;
    if(dstY<0)dstY=0;
    if(dstX+width>400) dstX = 400 - width;
    if(dstY+height>400) dstY = 400 - height;
    if(collision(&kyleRect,&insulinRect)){
        collected = true;
    }
    if(collected){
        quantity++;
        insX = rand()%(sWidth-insWidth);
        insY = rand()%(sHeight-insHeight);
        if((insX>=dstX&&insX<=dstX+width)&&(insY>=dstY&&insY<=dstY+height)){
            while((insX>=dstX&&insX<=dstX+width)&&(insY>=dstY&&insY<=dstY+height))insY = rand()%(sHeight-insHeight);
        }
        quantity++;
        collected = false;
    }
    }
    }else if(state==2||state==3){
        if(keys[SDLK_RETURN]){
            countDown = 120;
            timeWidth = 150;
            quantity = 0;
            srcX = 0;
            srcY = 0;
            dstX = 0;
            dstY = 0;
            kyle = SDL_LoadBMP("graphics/kyleFront1.bmp");
            bottlesLeft = SDL_LoadBMP("graphics/bottles5.bmp");
            state = 0;
        }
    }
}

void gameEvents::gameUpdate(){
    SDL_Flip(screen);
    if(1000/FPS>SDL_GetTicks()-start){
        SDL_Delay(1000/FPS-(SDL_GetTicks()-start));
    }
}

void gameEvents::gameClean(){
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_FreeSurface(screen);
    SDL_Quit();
    exit(0);
}

bool gameEvents::gameDone(){
    return done;
}

bool gameEvents::collision(SDL_Rect *rect1,SDL_Rect *rect2){
    if(rect1->y+2 >= rect2->y + rect2->h)return false; //bottom of target
    if(rect1->x+20 >= rect2->x + rect2->w)return false; //right of target
    if(rect1->y + rect1->h <= rect2->y+5)return false; //top of target
    if(rect1->x + rect1->w <= rect2->x+20)return false; //left of target
    return true;
}

void gameEvents::gameDraw(){
    //Main Menu State (state == 0)
    if(!state){
    drawBackground(0,0,titleScreen,screen);
    drawBackground(140,125,startButton,screen);
    drawBackground(140,225,exitButton,screen);
    }else if(state==1){

    //Play State (state == 1)
    kyleRect = gameSetRects(dstX,dstY,width,height);
    insulinRect = gameSetRects(insX,insY,insWidth,insHeight);
    drawBackground(0,0,background,screen);
    drawBackground(190,400,timeTitle,screen);
    if(quantity==2){
        bottlesLeft = SDL_LoadBMP("graphics/bottles4.bmp");
    }else if(quantity==4){
        bottlesLeft = SDL_LoadBMP("graphics/bottles3.bmp");
    }else if(quantity==6){
        bottlesLeft = SDL_LoadBMP("graphics/bottles2.bmp");
    }else if(quantity==8){
        bottlesLeft = SDL_LoadBMP("graphics/bottles1.bmp");
    }
    drawBackground(10,405,bottlesLeft,screen);
    drawRect(238,412,timeWidth,15,colour);
    if(countDown>90){
        drawBackground(135,140,three,screen);
    }else if(countDown>60){
        drawBackground(135,140,two,screen);
    }else if(countDown>30){
        drawBackground(135,140,one,screen);
    }else if(countDown>0){
        drawBackground(135,140,GO,screen);
    }
    if(!countDown){
    drawInsulin(insX,insY,insulin,screen);
    }
    SDL_SetColorKey(kyle,SDL_SRCCOLORKEY,SDL_MapRGB(kyle->format,1,249,0));
    drawSprite(srcX,srcY,dstX,dstY,width,height,kyle,screen);
    }else if(state==2){
    //Win State (state == 2)
    drawBackground(0,0,winScreen,screen);
    }else if(state==3){
    //Lose State (state == 3)
    drawBackground(0,0,loseScreen,screen);
    }
}

void gameEvents::drawBackground(int x,int y,SDL_Surface *source,SDL_Surface *destination){
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    SDL_BlitSurface(source,NULL,destination,&rect);
}

void gameEvents::drawInsulin(int x,int y,SDL_Surface *source,SDL_Surface *destination){
    if(!collected && quantity<10){
        SDL_Rect rect;
        rect.x = x;
        rect.y = y;
        rect.w = insWidth;
        rect.h = insHeight;
        SDL_BlitSurface(source,NULL,destination,&rect);
    }
}

void gameEvents::drawSprite(int srcX,int srcY,int dstX,int dstY,int width,int height,SDL_Surface *source,SDL_Surface *destination){
    SDL_Rect src;
    src.x = srcX;
    src.y = srcY;
    src.w = width;
    src.h = height;
    SDL_Rect dst;
    dst.x = dstX;
    dst.y = dstY;
    dst.w = width;
    dst.h = height;
    SDL_BlitSurface(source,&src,destination,&dst);
}

void gameEvents::drawRect(double x,double y,double w,double h,Uint32 colour){
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;
    SDL_FillRect(screen,&rect,colour);
}
