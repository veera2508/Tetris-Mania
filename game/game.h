#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "ui.h"
#include <vector>
#include "shape.h"

#ifndef TEXTURE_H
#include "texture.h"
#endif

#ifndef INIT_H
#include "init.h"
#endif

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

        //Free resources
        void free();

        //Set Position
        void setTexturePositions();

    private:
        //Render the game area background
        void renderGameAreaBackground();

        //Render Static Textures
        void renderStaticTextures();

        //Render dynamic textures
        void renderDynamicTextures();

        //Render the images
        void renderImages();

        //Render the Buttons
        void renderButtons();

        //Render current shape
        void renderCurrentShape();

        //Handle UI events
        void handleUIEvents(SDL_Event *e);

        //Load Images
        bool loadImages();

        //Load Buttons
        bool loadButtons();

        //Set image positions
        void setImagePositions();

        //Set button positions
        void setButtonPositions();

        //Screen dimensions
        int SCREEN_WIDTH;
        int SCREEN_HEIGHT;

        //Flag to check if game over
        bool Gameover;

        //Window
        SDL_Window *gWindow;

        //Renderer
        SDL_Renderer *gRenderer;

        //Image Textures
        LTexture images[IMAGE_TOTAL];

        //Game Phase
        GamePhase phase;

        //Buttons
        LButton buttons[BUTTON_TOTAL];

        //Game grid
        int grid[GRID_HEIGHT][GRID_WIDTH];

        //Block textures to render
        std::vector<Block> renderBlocs;

        Shape currentShape = NULL;
};

Game::Game(int SCREEN_WIDTH, int SCREEN_HEIGHT, SDL_Window *gWindow, SDL_Renderer *gRenderer)
{
    this->SCREEN_WIDTH = SCREEN_WIDTH;
    this->SCREEN_HEIGHT = SCREEN_HEIGHT;
    this->gWindow = gWindow;
    this->gRenderer = gRenderer;
    this->Gameover = false;
    for (int i = 0; i < 25; i++)
        for (int j = 0; j < 25; j++)
            grid[i][j] = 0;
}

Game::~Game()
{
    free();
}

bool Game::loadAssets()
{
    if (!loadImages()) return false;
    if (!loadButtons()) return false;
    return true;
}

bool Game::loadImages()
{
    if (!images[GAMEAREABACKGROUND].loadFromFile(gRenderer, "Assets/Images/gameAreaBackground.png")) return false;
    if (!images[LOGO].loadFromFile(gRenderer, "Assets/Images/Logo.png")) return false;
    return true;
}

bool Game::loadButtons()
{
    if (!buttons[START_BUTTON].loadFromFile(gRenderer, "Assets/Textures/UI/start_button.png")) return false;
    if (!buttons[STOP_BUTTON].loadFromFile(gRenderer, "Assets/Textures/UI/quit_button.png")) return false;
    return true;
}

void Game::setTexturePositions()
{
    setImagePositions();
    setButtonPositions();
}

void Game::setImagePositions()
{
    images[GAMEAREABACKGROUND].setPosition(SCREEN_WIDTH - images[GAMEAREABACKGROUND].getWidth() - 75, 35);
    images[LOGO].setPosition(100, 35);
}

void Game::setButtonPositions()
{
    buttons[START_BUTTON].setPosition(200, 300);
    buttons[STOP_BUTTON].setPosition(200, 400);
}

void Game::renderStaticTextures()
{
    renderImages();
    renderButtons();
}

void Game::renderImages()
{
    for (int i = 0; i < IMAGE_TOTAL; i++)
        images[i].render(gRenderer);
}

void Game::renderButtons()
{
    for (int i = 0; i < BUTTON_TOTAL; i++)
        buttons[i].render(gRenderer);
}

void Game::renderDynamicTextures()
{
    renderCurrentShape();
}

void Game::renderCurrentShape()
{
    int x, y;
    images[GAMEAREABACKGROUND].getPosition(x, y);
    currentShape.render(gRenderer, x, y);
}

void Game::handleUIEvents(SDL_Event *e)
{
    if (buttons[START_BUTTON].handleEvent(e))
        phase = ONGOING;
    
    if (buttons[STOP_BUTTON].handleEvent(e))
        Gameover = true;
}

bool Game::startGame()
{
    SDL_Event e;
    currentShape = Shape(gRenderer);
    currentShape.setRelativePosition(5, 10);
    currentShape.loadFromFile(gRenderer);
    loadAssets();
    setTexturePositions();
    phase = START;
    while (!Gameover)
    {
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
                Gameover = true;
            
            else
            {
                handleUIEvents(&e);
            }
        }
        SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0x00, 0xFF );
        SDL_RenderClear( gRenderer );
        if (phase == START)
        {
            renderStaticTextures();
        }
        else
        {
            renderStaticTextures();
            renderDynamicTextures();
        }
        SDL_RenderPresent( gRenderer );
    }
    
}

void Game::free() 
{
    //Free Textures
    for (int i = 0; i < IMAGE_TOTAL; i++)
        images[i].free();
    
    for (int i = 0; i < BUTTON_TOTAL; i++)
        buttons[i].free();

    SCREEN_WIDTH = SCREEN_HEIGHT = 0;
    gWindow = NULL;
    gRenderer = NULL;
    Gameover = false;
}
