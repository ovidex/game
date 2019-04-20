#include "window.h"

int main(int argc, char *args[])
{
    SDL_Window *gWindow;
    SDL_Renderer *gRenderer;

    //Start up SDL and create window
    int ret = Window::init(&gWindow, &gRenderer);
    if (ret < 0)
    {
        fprintf(stderr, "Failed to initialize: %d!\n", ret);
        return -1;
    }

    SDL_Texture *gTexture = Window::load_texture("i-love-c.png", gRenderer);

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
    while (Window::is_running(quit))
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
        Window::draw(gRenderer,gTexture);

    }

    //close SDL
    Window::cleanup();

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
