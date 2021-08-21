#include <iostream>
#include <SDL.h>
#include <complex>
#include <fstream>
// include mandelbrot header file
#include "mandelbrot.h"
// include domain header file
#include "domain.h"
//Screen dimensions and range
int SCREEN_WIDTH, SCREEN_HEIGHT;
double x_min, x_max, y_min, y_max;
// SDL WINDOW
SDL_Window *window = NULL;
//  SDL RENDERER
SDL_Renderer *renderer = NULL;
// SDL TEXTURE
SDL_Texture *texture = NULL;
// SDL PIXELS
Uint32 *pixels = NULL;
// initializes all the SDL parameters 
bool init()
{
    //Initialization flag
    bool success = true;

    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        success = false;
    }
    else
    {
        //Create window
        window = SDL_CreateWindow("Mandelbrot Set", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (window == NULL)
        {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
            success = false;
        }
        else
        {
            renderer = SDL_CreateRenderer(window, -1, 0);
            texture = SDL_CreateTexture(renderer,
                                        SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, SCREEN_WIDTH, SCREEN_HEIGHT);
            pixels = new Uint32[SCREEN_WIDTH * SCREEN_HEIGHT];

            memset(pixels, 255, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32));
        }
    }

    return success;
}
// deletion and deallocation
void close()
{
    delete[] pixels;
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);

    SDL_DestroyWindow(window);
    SDL_Quit();
}
// assigns rgb values to every pixel using the mandelbrot class
void plot()
{
    // range in which we define our mandelbrot 
    Domain<double> range(x_min, x_max, y_min, y_max);
    // mandelbrot object is created
    Mandelbrot mandelbrot(SCREEN_WIDTH, SCREEN_HEIGHT, range);
    std::tuple<int, int, int> rgb;

    int pitch = 0;
    Uint32 format;

    // Get the size of the texture.
    int w, h;
    SDL_QueryTexture(texture, &format, nullptr, &w, &h);

    // Now let's make our "pixels" pointer point to the texture data.
    if (!SDL_LockTexture(texture, nullptr, (void **)&pixels, &pitch))
    {
        // If the locking fails, you might want to handle it somehow. SDL_GetError(); or something here.
        std::cout<<"Error while locking texture"<<SDL_GetError();
    }
    SDL_PixelFormat pixelFormat;
    pixelFormat.format = format;
    // looping over all the pixels in the window and assigning them appropriate rgb values
    for (int x = 0; x <= SCREEN_WIDTH; x++)
    {
        for (int y = 0; y <= SCREEN_HEIGHT; y++)
        {
            rgb = mandelbrot.get_rgb(x, y);
            pixels[y * SCREEN_WIDTH + x] = SDL_MapRGB(&pixelFormat, std::get<0>(rgb), std::get<1>(rgb), std::get<2>(rgb));
        }
    }
    SDL_UnlockTexture(texture);
}
// reads data from the text file values 
bool readValues()
{
    std::ifstream filestream("../values.txt");
    if (!filestream)
        return false;
    filestream >> SCREEN_WIDTH >> SCREEN_HEIGHT >> x_min >> x_max >> y_min >> y_max;
    filestream.close();
    return true;
}

int main(int argc, char **argv)
{
    if (!readValues())
    {
        printf("Could not get values from txt file");
        return 0;
    }
    bool quit = false;
    SDL_Event event;
    if (init())
    {
        plot();
        while (!quit)
        {
            SDL_UpdateTexture(texture, NULL, pixels, SCREEN_WIDTH * sizeof(Uint32));

            SDL_WaitEvent(&event);
            if (event.type == SDL_QUIT)
            {
                quit = true;
            }
            SDL_RenderClear(renderer);
            SDL_RenderCopy(renderer, texture, NULL, NULL);
            SDL_RenderPresent(renderer);
        }

        close();

        return 0;
    }
}
