#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define INIT_H

enum Shapes
{
    S_SHAPE,
    Z_SHAPE,
    T_SHAPE,
    L_SHAPE,
    I_SHAPE,
    ML_SHAPE,
    SQR_SHAPE,
    SHAPE_TOTAL
};

enum Colors
{
    BLUE,
    GREEN,
    PURPLE,
    PINK,
    RED,
    YELLOW,
    TEAL,
    COLOR_TOTAL
};

enum GamePhase
{
    START,
    ONGOING,
    QUIT
};

enum EImage
{
    GAMEAREABACKGROUND,
    LOGO,
    LEVEL1,
    LEVEL2,
    LEVEL3,
    IMAGE_TOTAL
};

enum EButton
{
    START_BUTTON,
    STOP_BUTTON,
    BUTTON_TOTAL
};

//Grid dimension
const int GRID_WIDTH = 15;
const int GRID_HEIGHT = 30;

//Screen dimension constants
const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 1000;

SDL_Renderer *init(SDL_Window *gWindow, SDL_Renderer *gRenderer) {
    bool success = true;
    if ( SDL_Init( SDL_INIT_VIDEO ) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        success = false;
    }
    else {
        gWindow = SDL_CreateWindow( "Tetris Mania", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (gWindow == NULL) {
            printf("Window could not be created! SDL_Error: %s\n");
            success = false;
        }
        else {
            //Create renderer for window instead of surface
            gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            if ( gRenderer == NULL ) {
                printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
                success = false;
            }
            else {
                //Initialize renderer color
                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

                //Initialize loading for png
                int imgFlags = IMG_INIT_PNG; //flag for png loading
                //We pass the flags required to load and it returns flags successfully loaded
                if ( !( IMG_Init( imgFlags ) & imgFlags ) ) {
                    printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
                    success = false;
                }
                
                #if defined(SDL_TTF_MAJOR_VERSION)
                if (TTF_Init() == -1) {
                    printf("SDL_ttf could not be initialized! Error: %s\n", TTF_GetError());
                    success = false;
                }
                #endif
            }
        }
        
    }

    return gRenderer;
}

void close(SDL_Window *gWindow, SDL_Renderer *gRenderer) {

    SDL_DestroyRenderer( gRenderer );
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;
    gRenderer = NULL;

    IMG_Quit();
    SDL_Quit();
}