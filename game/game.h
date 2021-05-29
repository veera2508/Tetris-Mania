#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "texture.h"

class Game 
{
    public:
        //Constructor
        Game(int SCREEN_WIDTH, int SCREEN_HEIGHT, SDL_Window *gWindow, SDL_Renderer *gRenderer);

        //Destructor
        ~Game();

        //Load the media files
        bool loadAssets();

        //Start Game
        bool startGame();

        //Render Textures
        void renderTextures();

        //Free resources
        void free();

    private:
        //Render the game area background
        void renderGameAreaBackground();

        //Screen dimensions
        int SCREEN_WIDTH;
        int SCREEN_HEIGHT;

        //Flag to check if game over
        bool Gameover;

        //Window
        SDL_Window *gWindow;

        //Renderer
        SDL_Renderer *gRenderer;

        //Game Area Background
        LTexture gameAreaBackground;

};

Game::Game(int SCREEN_WIDTH, int SCREEN_HEIGHT, SDL_Window *gWindow, SDL_Renderer *gRenderer)
{
    this->SCREEN_WIDTH = SCREEN_WIDTH;
    this->SCREEN_HEIGHT = SCREEN_HEIGHT;
    this->gWindow = gWindow;
    this->gRenderer = gRenderer;
    this->Gameover = false;
}

Game::~Game()
{
    free();
}

bool Game::loadAssets()
{
    gameAreaBackground.loadFromFile(gRenderer, "Assets/Images/gameAreaBackground.png");
    return true;
}

void Game::renderTextures()
{
    renderGameAreaBackground();
}

void Game::renderGameAreaBackground()
{
    gameAreaBackground.render(gRenderer, SCREEN_WIDTH/2 - gameAreaBackground.getWidth()/2, 200 );
}

bool Game::startGame()
{
    SDL_Event e;
    loadAssets();
    while (!Gameover)
    {
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
                Gameover = true;
        }

        SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0x00, 0xFF );
        SDL_RenderClear( gRenderer );
        renderTextures();
        SDL_RenderPresent( gRenderer );
    }
}

void Game::free() 
{
    SCREEN_WIDTH = SCREEN_HEIGHT = 0;
    gWindow = NULL;
    gRenderer = NULL;
    Gameover = false;
}
