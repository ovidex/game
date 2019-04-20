#include "window.h"

int main(int argc, char *args[])
{Window *wind;
//Window();
     SDL_Window* gWindow ;
    SDL_Renderer* gRenderer;
    //Start up SDL and create window
    int ret = wind->init(&gWindow, &gRenderer);
    if (ret < 0)
    {
        fprintf(stderr, "Failed to initialize: %d!\n", ret);
        return -1;
    }

    SDL_Texture *gTexture = wind->load_texture("i-love-c.png", gRenderer);

    //Load media
    if (!gTexture)
    {
        fprintf(stderr, "Failed to load media!\n");
        //Destroy window
        SDL_DestroyRenderer(gRenderer);
        SDL_DestroyWindow(gWindow);
        gWindow = NULL;
        gRenderer = NULL;

        return -1;
    }
    //Main loop flag
    bool quit = false;

    //Event handler
    SDL_Event e;

    //While application is running
    while (wind->is_running(quit))
    {
        //Handle events on queue
        while (SDL_PollEvent(&e) != 0)
        {
            //User requests quit
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }
        }
        wind->draw(gRenderer,gTexture);

    }

    //close SDL
    wind->cleanup();

    //Free loaded image
    SDL_DestroyTexture(gTexture);
    gTexture = NULL;

    //Destroy window
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    gRenderer = NULL;

    return 0;
}
