#include "SdlApp.h"

SdlApp::SdlApp(const std::string &title, int width, int height)
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
    // 设置背景色为黑色并清空屏幕
    SDL_SetRenderDrawColor(renderer.get(), 0, 0, 0, 255);
    SDL_RenderClear(renderer.get());

    // 设置你想要绘制点的颜色
    SDL_SetRenderDrawColor(renderer.get(), 255, 0, 0, 255); // 红色

    // 指定点的坐标 (例如在 (300, 200) 处画一个点)
    int x = 0;
    int y = 0;
    SDL_RenderDrawPoint(renderer.get(), x, y); // 在指定坐标画点

    // 示例：绘制一个红色矩形
    SDL_Rect rect = {200, 150, 400, 300};
    SDL_SetRenderDrawColor(renderer.get(), 255, 0, 0, 255);
    SDL_RenderFillRect(renderer.get(), &rect);

    // 刷新渲染器，展示绘制的内容
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

void SdlApp::setWindowTitleWithFPS()
{
    std::string title = "My Rasterizer - FPS: " + std::to_string(static_cast<int>(currentFPS));
    SDL_SetWindowTitle(window.get(), title.c_str());
}
