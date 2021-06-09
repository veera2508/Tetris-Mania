#include "init.hpp"
#include "game.hpp"

int main(int argc, char *args[])
{
    SDL_Window *gWindow = NULL;
    SDL_Renderer *gRenderer = NULL;
    gRenderer = init(gWindow, gRenderer);
    Game tetris = Game(SCREEN_WIDTH, SCREEN_HEIGHT, gWindow, gRenderer);
    tetris.startGame();
    close(gWindow, gRenderer);
}


