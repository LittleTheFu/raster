#ifndef SDLAPP_H
#define SDLAPP_H

#include <SDL.h>
#include <memory>
#include <string>
#include <iostream>

#include "scene.h"
#include "zbuffer.h"
#include "texture.h"

class SdlApp {
public:
    SdlApp(const std::string& title, int width, int height);
    ~SdlApp();

    bool isRunning() const { return running; }
    void handleEvents();
    void render();
    void updateFPS();

    void setPixel(int x, int y, Uint8 r, Uint8 g, Uint8 b, Uint8 a);
    void drawTriangle(const Vertex& v0, const Vertex& v1, const Vertex& v2);

    Vertex interpolateVertex(const Vertex &v0, const Vertex &v1, int y) const;
private:
    Scene scene;
    ZBuffer zBuffer;
    Texture texture;

private:
    struct SDLWindowDeleter {
        void operator()(SDL_Window* ptr) const { if (ptr) SDL_DestroyWindow(ptr); }
    };

    struct SDLRendererDeleter {
        void operator()(SDL_Renderer* ptr) const { if (ptr) SDL_DestroyRenderer(ptr); }
    };

    std::unique_ptr<SDL_Window, SDLWindowDeleter> window;
    std::unique_ptr<SDL_Renderer, SDLRendererDeleter> renderer;

    bool running = true;
    int frameCount = 0;
    Uint32 lastTime = 0;
    float currentFPS = 0.0f;

    void setWindowTitleWithFPS();
};

#endif // SDLAPP_H