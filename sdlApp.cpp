#include "SdlApp.h"

SdlApp::SdlApp(const std::string &title, int width, int height)
    : scene(width, height),
      width(width),
      height(height),
      zBuffer(width, height)
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0)
    {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        running = false;
        return;
    }

    window.reset(SDL_CreateWindow(title.c_str(),
                                  SDL_WINDOWPOS_CENTERED,
                                  SDL_WINDOWPOS_CENTERED,
                                  width,
                                  height,
                                  SDL_WINDOW_SHOWN));
    if (!window)
    {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        running = false;
        return;
    }

    renderer.reset(SDL_CreateRenderer(window.get(), -1, SDL_RENDERER_ACCELERATED));
    if (!renderer)
    {
        std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        running = false;
        return;
    }

    texture.reset(SDL_CreateTexture(renderer.get(),
                                      SDL_PIXELFORMAT_RGBA8888,
                                      SDL_TEXTUREACCESS_STREAMING,
                                      width,
                                      height));
    if (!texture)
    {
        std::cerr << "SDL_CreateTexture Error: " << SDL_GetError() << std::endl;
        running = false;
        return;
    }

    lastTime = SDL_GetTicks();
}

SdlApp::~SdlApp()
{
    SDL_Quit();
}

void SdlApp::handleEvents()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT ||
            (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE))
        {
            running = false;
        }
    }
}


void SdlApp::render()
{
    SDL_RenderClear(renderer.get());

    scene.run(); // 运行场景
    
    copyFrameBufferToTexture(); // 将帧缓冲区复制到纹理
    SDL_RenderPresent(renderer.get());
}

void SdlApp::updateFPS()
{
    frameCount++;
    Uint32 currentTime = SDL_GetTicks();
    if (currentTime - lastTime >= 1000)
    {
        currentFPS = frameCount * 1000.0f / (currentTime - lastTime);
        frameCount = 0;
        lastTime = currentTime;
        setWindowTitleWithFPS();
    }
}

void SdlApp::setPixel(int x, int y, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    SDL_SetRenderDrawColor(renderer.get(), r, g, b, a);
    SDL_RenderDrawPoint(renderer.get(), x, y);
}

void SdlApp::copyFrameBufferToTexture()
{
    void* texturePixels;
    int texturePitch;
    if (SDL_LockTexture(texture.get(), nullptr, &texturePixels, &texturePitch) < 0) {
        SDL_Log("SDL_LockTexture failed: %s", SDL_GetError());
        return;
    }

    const uint8_t* colorBufferData = scene.getFrameBuffer().getColorBuffer().getBuffer().data();

    int colorBufferRowBytes = width * 4;
    int textureRowBytes = texturePitch;
    uint8_t* destRow = static_cast<uint8_t*>(texturePixels);
    const uint8_t* srcRow = colorBufferData;

    for (int y = 0; y < height; ++y) {
        std::memcpy(destRow, srcRow, colorBufferRowBytes);
        destRow += textureRowBytes;
        srcRow += colorBufferRowBytes;
    }

    SDL_UnlockTexture(texture.get());
    SDL_RenderCopy(renderer.get(), texture.get(), nullptr, nullptr);
}

void SdlApp::setWindowTitleWithFPS()
{
    std::string title = "My Rasterizer - FPS: " + std::to_string(static_cast<int>(currentFPS));
    SDL_SetWindowTitle(window.get(), title.c_str());
}
