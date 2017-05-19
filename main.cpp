#include "gameEvents.h"

int main(int argc, char** argv){
    gameEvents ge;
    ge.gameInit();
    while(!ge.gameDone()){
        ge.gameInput();
        ge.gameDraw();
        ge.gameUpdate();
    }
    ge.gameClean();
    return 0;
}
