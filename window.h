#pragma once
//#include "drawable.h"
//#include "runnable.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
class Window: public Drawable, public Runnable
{
public:
    SDL_Window* gWindowx ;
    SDL_Renderer* gRendererx;
    Window()
    {
        gWindowx = NULL;
        gRendererx = NULL;
    }


// init sdl and create gWindowx and gRendererx
    int init(SDL_Window **gWindowx, SDL_Renderer **gRendererx)
    {
        //Initialize SDL
        if (SDL_Init(SDL_INIT_VIDEO) < 0)
        {
            fprintf(stderr, "SDL could not initialize! SDL Error: %s\n", SDL_GetError());
            return -1;
        }
        //Set texture filtering to linear
        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
        {
            printf("Warning: Linear texture filtering not enabled!\n");
        }

        //Create window
        *gWindowx = SDL_CreateWindow("SDL window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (*gWindowx == NULL)
        {
            fprintf(stderr, "Window could not be created! SDL Error: %s\n", SDL_GetError());
            return -2;
        }

        //Create renderer for window
        *gRendererx = SDL_CreateRenderer(*gWindowx, -1, SDL_RENDERER_ACCELERATED);
        if (*gRendererx == NULL)
        {
            fprintf(stderr, "Renderer could not be created! SDL Error: %s\n", SDL_GetError());
            return -3;
        }
        //Initialize renderer color
        SDL_SetRenderDrawColor(*gRendererx, 0xFF, 0xFF, 0xFF, 0xFF);

        //Initialize PNG loading
        int imgFlags = IMG_INIT_PNG;
        if (!(IMG_Init(imgFlags) & imgFlags))
        {
            fprintf(stderr, "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
            return -4;
        }

        return 0;
    }

// load a texture from path using gRendererx (returned from init!!!)
    SDL_Texture *load_texture(const std::string &path, SDL_Renderer *gRendererx)
    {
        //The final texture
        SDL_Texture *newTexture = NULL;

        //Load image at specified path
        SDL_Surface *loadedSurface = IMG_Load(path.c_str());
        if (loadedSurface == NULL)
        {
            fprintf(stderr, "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
            return NULL;
        }
        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface(gRendererx, loadedSurface);
        if (newTexture == NULL)
        {
            fprintf(stderr, "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
            return NULL;
        }

        //Get rid of old loaded surface
        SDL_FreeSurface(loadedSurface);

        return newTexture;
    }

// quit sdl and img. You have to free surfaces, textures and renderers yourself
    void cleanup()
    {
        //Quit SDL subsystems
        IMG_Quit();
        SDL_Quit();
    }
    bool is_running(bool quit)
    {
        if(quit==false)
            return true;
        return false;
    }
    void draw(SDL_Renderer *gRendererx,SDL_Texture *gTexture)
    {
//Clear screen
        SDL_RenderClear(gRendererx);

        //Render texture to screen
        SDL_RenderCopy(gRendererx, gTexture, NULL, NULL);

        //Update screen
        SDL_RenderPresent(gRendererx);
    }
};
