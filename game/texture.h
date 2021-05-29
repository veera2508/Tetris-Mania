#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

class LTexture 
{
    public:
        //ConstructorColor Modulation of textures
        LTexture();

        //Destructor
        ~LTexture();

        //Load image into texture
        bool loadFromFile( SDL_Renderer *gRenderer, std::string path );

        //Dealocates texture
        void free();

        #if defined(SDL_TTF_MAJOR_VERSION)
        //Creates image from font string
        bool loadFromRenderedText(std::string textureText, SDL_Color textColor);
        #endif

        //Renders texture at a given point
        void render( SDL_Renderer* gRenderer, int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

        //Set color modulation
        void setColor( Uint8 red, Uint8 green, Uint8 blue );

        //Set blending
        void setBlendMode( SDL_BlendMode blending );

        //set alpha modulation
        void setAlpha( Uint8 alpha );

        //Gets image dimensions
        int getWidth();
        int getHeight();

    private:
        //Hardware Texture
        SDL_Texture* mTexture;

        //Image Dimensions
        int mWidth;
        int mHeight;
};

LTexture::LTexture() 
{
    mTexture = NULL;
    mWidth = 0;
    mHeight = 0;
}

LTexture::~LTexture() 
{
    free();
}

bool LTexture::loadFromFile( SDL_Renderer *gRenderer, std::string path ) 
{
    //Delete the previous texture
    free();
    SDL_Texture* newTexture = NULL;
    //Surface to store the image
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if ( loadedSurface == NULL )
        printf( "Unable to load image! SDL Error: %s\n", IMG_GetError() );
    
    else 
    {
        //Create texture from surface pixels

        //SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ));
        newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
        if (newTexture == NULL) 
            printf("Unable to create texture! SDL Error:%s\n", SDL_GetError());

        else 
        {
            //Store image dimesions
            mWidth = loadedSurface->w;
            mHeight = loadedSurface->h;
        }
        
        //get rid of old surface
        SDL_FreeSurface(loadedSurface);
    }
    mTexture = newTexture;
    return mTexture != NULL;
}

void LTexture::free() 
{
    //Free texture if it exists
    if (mTexture != NULL) 
    {
        SDL_DestroyTexture( mTexture );
        mHeight = 0;
        mWidth = 0;
    }
}

#if defined(SDL_TTF_MAJOR_VERSION)
bool LTexture::loadFromRenderedText(std::string textureText, SDL_Color textColor) 
{
    //Free the previous texture
    free();
    //Render text surface
    SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, textureText.c_str(), textColor);
    if (textSurface == NULL)
        printf("Unable to render text surface! SDL Error: %s\n", TTF_GetError());
    else 
    {
        mTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
        if (mTexture == NULL)
            printf("Cannot create texture! SDL Error: %s\n", SDL_GetError());
        else 
        {
            //Set image dimensions
            mWidth = textSurface->w;
            mHeight = textSurface->h;
        }
        SDL_FreeSurface(textSurface);
    }

    //Return success or failure
    return mTexture != NULL; 
}
#endif

void LTexture::render( SDL_Renderer *gRenderer, int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip ) 
{
    SDL_Rect renderquad = { x, y, mWidth, mHeight };
    //Set clip rendering dimensions
    if (clip != NULL) 
    {
        renderquad.w = clip->w;
        renderquad.h = clip->h;
    }
    //Render to screen
    SDL_RenderCopyEx(gRenderer, mTexture, clip, &renderquad, angle, center, flip);
}

void LTexture::setColor( Uint8 red, Uint8 green, Uint8 blue ) 
{   
    //Modulate Texture
    SDL_SetTextureColorMod( mTexture, red, green, blue );
}

void LTexture::setBlendMode( SDL_BlendMode blending ) 
{
    //Set blending function
    SDL_SetTextureBlendMode( mTexture, blending );
}

void LTexture::setAlpha( Uint8 alpha ) 
{
    SDL_SetTextureAlphaMod( mTexture, alpha );
}

int LTexture::getHeight() 
{
    return mHeight;
}

int LTexture::getWidth() 
{
    return mWidth;
}
