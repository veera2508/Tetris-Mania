#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <cmath>

#ifndef TEXTURE_H
#include "texture.h"
#endif

class LButton 
{
    public:
        //Initializes internal variables
        LButton();

        //Load texture from file
        bool loadFromFile(SDL_Renderer *gRenderer, std::string path);

        //Set top left position
        void setPosition( int x, int y );

        //Handles mouse event
        bool handleEvent( SDL_Event* e );
    
        //Shows button sprite
        void render(SDL_Renderer *gRenderer);

        //Free texture
        void free();

    private:
        //Top left position
        SDL_Point mPosition;

        //Button Texture
        LTexture texture;

        //Button Name
        std::string name;
};

LButton::LButton() 
{
    mPosition.x = 0;
    mPosition.y = 0;
}

void LButton::setPosition(int x, int y) 
{
    mPosition.x = x;
    mPosition.y = y;
    texture.setPosition(x, y);
}

void LButton::free()
{
    texture.free();
}

bool LButton::handleEvent(SDL_Event* e) 
{
    //If mouse event happend
    if ( e->type == SDL_MOUSEBUTTONDOWN ) 
    {
        //Get mouse position
        int x, y;
        SDL_GetMouseState( &x, &y );
        bool inside = false;

        //Check if mouse is inside button
        if (x >= mPosition.x && x <= mPosition.x + texture.getWidth() && y >= mPosition.y && y <= mPosition.y + texture.getHeight())
            inside = true;

        //Mouse is outside button
        if (!inside)
            return false;
            
        //Mouse is inside button
        else
            return true;
    }
}

bool LButton::loadFromFile(SDL_Renderer *gRenderer, std::string path)
{
    if (!texture.loadFromFile(gRenderer, path)) return false;
    return true;
}

void LButton::render(SDL_Renderer *gRenderer)
{
    texture.render(gRenderer);
}







