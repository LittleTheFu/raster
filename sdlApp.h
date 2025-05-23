#ifndef SDLAPP_H
#define SDLAPP_H

#include <SDL.h>
#include <memory>
#include <string>
#include <iostream>

#include "scene.h"
#include "zbuffer.h"
#include "texture.h"

class SdlApp
{
public:
    SdlApp(const std::string &title, int width, int height, int shadowMapSize);
    ~SdlApp();

    bool isRunning() const { return running; }
    void handleEvents();
    void render();
    void updateFPS();

    void setPixel(int x, int y, Uint8 r, Uint8 g, Uint8 b, Uint8 a);
    void copyFrameBufferToTexture();

private:
    Scene scene;
    ZBuffer zBuffer;

    int width;
    int height;

private:
    struct SDLWindowDeleter
    {
        void operator()(SDL_Window *ptr) const
        {
            if (ptr)
                SDL_DestroyWindow(ptr);
        }
    };

    struct SDLRendererDeleter
    {
        void operator()(SDL_Renderer *ptr) const
        {
            if (ptr)
                SDL_DestroyRenderer(ptr);
        }
    };

    struct SDLTextureDeleter
    {
        void operator()(SDL_Texture *ptr) const
        {
            if (ptr)
            {
                SDL_DestroyTexture(ptr);
                SDL_Log("SDL Texture destroyed.");
            }
        }
    };

    std::unique_ptr<SDL_Window, SDLWindowDeleter> window;
    std::unique_ptr<SDL_Renderer, SDLRendererDeleter> renderer;
    std::unique_ptr<SDL_Texture, SDLTextureDeleter> texture;
    

    bool running = true;
    int frameCount = 0;
    Uint32 lastTime = 0;
    float currentFPS = 0.0f;

    void setWindowTitleWithFPS();
};

#endif // SDLAPP_H