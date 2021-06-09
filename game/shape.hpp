#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include <cstdlib>
#include <ctime>

#ifndef TEXTURE_H
#include "texture.hpp"
#endif

#ifndef INIT_H
#include "init.hpp"
#endif

class Block
{
    public:
        //Constructoe
        Block();

        //Destructor
        ~Block();

        //Check if outside grid
        bool checkGrid();

        //Set relative position
        void setCentrePosition(int x, int y);

        //Get centre position
        void getCentrePosition(int &x, int &y);

        //Get offset position
        void getOffsetPosition(int &x, int &y);

        //Update offset
        void updateOffset(int off_x, int off_y);

        //Load from file
        void loadFromFile(SDL_Renderer *gRenderer, std::string filepath);

        //Get grid position
        void getGridPosition(int &x, int &y);

        //Render
        void render(SDL_Renderer *gRenderer, int grid_x, int grid_y);

    private:
        //Centre point
        int x, y;

        //Offset values
        int off_x, off_y;

        //Texture
        LTexture texture;
};

Block::Block()
{
    x = GRID_WIDTH/2;
    y = 0;

    off_x = 0;
    off_y = 0;
}

Block::~Block()
{
    texture.free();
    x = y = off_x = off_y = 0;
}

bool Block::checkGrid()
{
    int gloc_x = x + off_x;
    int gloc_y = y + off_y;

    if (gloc_x >= 0 && gloc_x < GRID_WIDTH && gloc_y >= 0 && gloc_y < GRID_HEIGHT)
        return true;

    return false;
}

void Block::setCentrePosition(int x, int y)
{
    this->x = x;
    this->y = y;
}

void Block::getCentrePosition(int &x, int &y)
{
    x = this->x;
    y = this->y;
}

void Block::getOffsetPosition(int &x, int &y)
{
    x = this->off_x;
    y = this->off_y;
}

void Block::getGridPosition(int &x, int &y)
{
    x = this->x + off_x;
    y = this->y + off_y;
}

void Block::updateOffset(int off_x, int off_y)
{
    this->off_x = off_x;
    this->off_y = off_y;
}

void Block::loadFromFile(SDL_Renderer *gRenderer, std::string filepath)
{
    texture.loadFromFile(gRenderer, filepath);
}

void Block::render(SDL_Renderer *gRenderer, int grid_x, int grid_y)
{
    texture.setPosition(grid_x + ((x+off_x) * texture.getWidth()), grid_y + ((y+off_y) * texture.getHeight()));
    texture.render(gRenderer);
}



class Shape
{
    public:

        //Constructor
        Shape(SDL_Renderer *gRenderer, int shape_type = -1);

        //Destructor
        ~Shape();

        //Move down
        void moveDown();

        //Move left
        void moveLeft();

        //Move right
        void moveRight();

        //Flip if possible
        void flipAngle();

        //Rotate by pi
        void rotateByPi();

        //Rotate by pi/2
        void rotateByPi2();

        //Set relative position
        void setRelativePosition(int x, int y);

        //Load from file
        bool loadFromFile(SDL_Renderer *gRenderer);

        //Get relative position
        void getRelativePosition(int &x, int &y);

        //Check if settled
        bool checkSettled(int grid[GRID_HEIGHT][GRID_WIDTH]);

        //Render
        void render(SDL_Renderer *gRenderer, int grid_x, int grid_y);
    
    private:
        //Shape type
        Shapes type;

        //Color of the shape
        Colors color;

        //Blocks vector 0th block is the center
        Block blocks[4];

        //Relative position
        int x, y;

        //Flip mode
        int flipmode;

};

Shape::Shape(SDL_Renderer *gRenderer, int shape_type)
{
    if (shape_type == -1)
    {
        int randno = rand() % SHAPE_TOTAL;
        //Set shape type
        type = Shapes(randno);

        //Set shape color
        color = Colors(randno);
    }
    else
    {
        //Set shape type
        type = Shapes(shape_type);

        //Set shape color
        color = Colors(shape_type);
    }

    switch(type)
    {
        case S_SHAPE:
        blocks[1].updateOffset(0, -1);
        blocks[2].updateOffset(-1, 0);
        blocks[3].updateOffset(-1, 1);
        break;

        case Z_SHAPE:
        blocks[1].updateOffset(0, -1);
        blocks[2].updateOffset(1, 0);
        blocks[3].updateOffset(-1, -1);
        break;

        case T_SHAPE:
        blocks[1].updateOffset(0, -1);
        blocks[2].updateOffset(-1, 0);
        blocks[3].updateOffset(1, 0);
        break;
        
        case L_SHAPE:
        blocks[1].updateOffset(0, -1);
        blocks[2].updateOffset(0, -2);
        blocks[3].updateOffset(1, 0);
        break;

        case I_SHAPE:
        blocks[1].updateOffset(0, -1);
        blocks[2].updateOffset(0, -2);
        blocks[3].updateOffset(0, 1);
        break;

        case ML_SHAPE:
        blocks[1].updateOffset(0, -1);
        blocks[2].updateOffset(0, -2);
        blocks[3].updateOffset(-1, 0);
        break;

        case SQR_SHAPE:
        blocks[1].updateOffset(0, 1);
        blocks[2].updateOffset(1, 0);
        blocks[3].updateOffset(1, 1);
        break;
    }
}

bool Shape::loadFromFile(SDL_Renderer *gRenderer)
{
    std::string filepath;
    switch(color)
    {
        case BLUE:
        filepath = "Assets/Textures/Blocks/Blue_Block.png";
        break;

        case GREEN:
        filepath = "Assets/Textures/Blocks/Green_Block.png";
        break;

        case PURPLE:
        filepath = "Assets/Textures/Blocks/Purple_Block.png";
        break;

        case PINK:
        filepath = "Assets/Textures/Blocks/Pink_Block.png";
        break;

        case RED:
        filepath = "Assets/Textures/Blocks/Red_Block.png";
        break;

        case TEAL:
        filepath = "Assets/Textures/Blocks/Teal_Block.png";
        break;

        case YELLOW:
        filepath = "Assets/Textures/Blocks/Yellow_Block.png";
        break;
    }

    for (int i = 0; i < 4; i++)
        blocks[i].loadFromFile(gRenderer, filepath);
}


Shape::~Shape()
{
    x = y = 0;
}

void Shape::setRelativePosition(int x, int y)
{
    this->x = x;
    this->y = y;
    for (int i = 0; i < 4; i++)
        blocks[i].setCentrePosition(x, y);
}

void Shape::getRelativePosition(int &x, int &y)
{
    x = this->x;
    y = this->y;
}

void Shape::render(SDL_Renderer *gRenderer, int grid_x, int grid_y)
{
    for (int i = 0; i < 4; i++)
        blocks[i].render(gRenderer, grid_x, grid_y);
}

void Shape::moveLeft()
{
    bool outside_grid = false;
    for (int i = 0; i < 4; i++)
    {
        int x, y;
        blocks[i].getCentrePosition(x, y);
        blocks[i].setCentrePosition(x - 1, y);
        if (!blocks[i].checkGrid())
            outside_grid = true;
        blocks[i].setCentrePosition(x, y);
    }

    if (!outside_grid)
    {
        for (int i = 0; i < 4; i++)
        {
            int x, y;
            blocks[i].getCentrePosition(x, y);
            blocks[i].setCentrePosition(x - 1, y);
        }   
    }
}

void Shape::moveRight()
{
    bool outside_grid = false;
    for (int i = 0; i < 4; i++)
    {
        int x, y;
        blocks[i].getCentrePosition(x, y);
        blocks[i].setCentrePosition(x + 1, y);
        if (!blocks[i].checkGrid())
            outside_grid = true;
        blocks[i].setCentrePosition(x, y);
    }

    if (!outside_grid)
    {
        for (int i = 0; i < 4; i++)
        {
            int x, y;
            blocks[i].getCentrePosition(x, y);
            blocks[i].setCentrePosition(x + 1, y);
        }   
    }
}

void Shape::moveDown()
{
    bool outside_grid = false;
    for (int i = 0; i < 4; i++)
    {
        int x, y;
        blocks[i].getCentrePosition(x, y);
        blocks[i].setCentrePosition(x, y + 1);
        if (!blocks[i].checkGrid())
            outside_grid = true;
        blocks[i].setCentrePosition(x, y);
    }

    if (!outside_grid)
    {
        for (int i = 0; i < 4; i++)
        {
            int x, y;
            blocks[i].getCentrePosition(x, y);
            blocks[i].setCentrePosition(x, y + 1);
        }   
    }
}

void Shape::rotateByPi2()
{
    int off_x, off_y;
    int off_x_rot, off_y_rot;
    bool outside_grid = false;
    for (int i = 1; i < 4; i++)
    {
        blocks[i].getOffsetPosition(off_x, off_y);
        off_x_rot = off_x * 0 + off_y * -1;
        off_y_rot = off_x * 1 + off_y * 0;
        blocks[i].updateOffset(off_x_rot, off_y_rot);
        if (!blocks[i].checkGrid())
            outside_grid = true;
        blocks[i].updateOffset(off_x, off_y);
    }

    if (!outside_grid)
    {
        for (int i = 1; i < 4; i++)
        {
            blocks[i].getOffsetPosition(off_x, off_y);
            off_x_rot = off_x * 0 + off_y * -1;
            off_y_rot = off_x * 1 + off_y * 0;
            blocks[i].updateOffset(off_x_rot, off_y_rot);
        }
    }
}

void Shape::flipAngle()
{
    switch(type)
    {
        case S_SHAPE:
        case I_SHAPE:
        case Z_SHAPE:
        rotateByPi2();
        break;

        case T_SHAPE:
        case L_SHAPE:
        case ML_SHAPE:
        rotateByPi2();
        break;
    }
}