#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "ui.h"

#ifndef TEXTURE_H
#include "texture.h"
#endif

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

enum EBlock
{
    BLUE,
    GREEN,
    PURPLE,
    PINK,
    RED,
    YELLOW,
    BLOCK_TOTAL
};

enum EButton
{
    START_BUTTON,
    STOP_BUTTON,
    BUTTON_TOTAL
};

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

        //Render Static Textures
        void renderStaticTextures();

        //Free resources
        void free();

        //Set Position
        void setTexturePositions();

    private:
        //Render the game area background
        void renderGameAreaBackground();

        //Render the images
        void renderImages();

        //Render the Buttons
        void renderButtons();

        //Handle UI events
        void handleUIEvents(SDL_Event *e);

        //Load Images
        bool loadImages();

        //Load Blocks
        bool loadBlocks();

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

        //Blocks
        LTexture blocks[BLOCK_TOTAL];

        //Buttons
        LButton buttons[BUTTON_TOTAL];
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
    if (!loadImages()) return false;
    if (!loadBlocks()) return false;
    if (!loadButtons()) return false;
    return true;
}

bool Game::loadImages()
{
    if (!images[GAMEAREABACKGROUND].loadFromFile(gRenderer, "Assets/Images/gameAreaBackground.png")) return false;
    if (!images[LOGO].loadFromFile(gRenderer, "Assets/Images/Logo.png")) return false;
    return true;
}

bool Game::loadBlocks()
{
    if (!blocks[BLUE].loadFromFile(gRenderer, "Assets/Textures/Blocks/Blue_Block.png")) return false;
    if (!blocks[GREEN].loadFromFile(gRenderer, "Assets/Textures/Blocks/Green_Block.png")) return false;
    if (!blocks[PINK].loadFromFile(gRenderer, "Assets/Textures/Blocks/Pink_Block.png")) return false;
    if (!blocks[PURPLE].loadFromFile(gRenderer, "Assets/Textures/Blocks/Purple_Block.png")) return false;
    if (!blocks[RED].loadFromFile(gRenderer, "Assets/Textures/Blocks/Red_Block.png")) return false;
    if (!blocks[YELLOW].loadFromFile(gRenderer, "Assets/Textures/Blocks/Yellow_Block.png")) return false;
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
    images[LOGO].setPosition(75, 35);
}

void Game::setButtonPositions()
{
    buttons[START_BUTTON].setPosition(175, 300);
    buttons[STOP_BUTTON].setPosition(175, 400);
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

void Game::handleUIEvents(SDL_Event *e)
{
    if (buttons[START_BUTTON].handleEvent(e))
        printf("Game Started!\n");
    
    if (buttons[STOP_BUTTON].handleEvent(e))
        Gameover = true;
}

bool Game::startGame()
{
    SDL_Event e;
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
        SDL_RenderPresent( gRenderer );
    }
    
}

void Game::free() 
{
    //Free Textures
    for (int i = 0; i < IMAGE_TOTAL; i++)
        images[i].free();
    
    for (int i = 0; i < BLOCK_TOTAL; i++)
        blocks[i].free();
    
    for (int i = 0; i < BUTTON_TOTAL; i++)
        buttons[i].free();

    SCREEN_WIDTH = SCREEN_HEIGHT = 0;
    gWindow = NULL;
    gRenderer = NULL;
    Gameover = false;
}
