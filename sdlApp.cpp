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

    // 绘制三角形的三个顶点
    auto screenCoords = scene.getTriangleScreenCoords();
    for (auto it = screenCoords.begin(); it != screenCoords.end(); it += 3)
    {
        if (it + 2 < screenCoords.end())
        {
            drawTriangle(*it, *(it + 1), *(it + 2));
        }
       
    }

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

void SdlApp::drawTriangle(const Vertex &v0, const Vertex &v1, const Vertex &v2)
{
    SDL_SetRenderDrawColor(renderer.get(), v0.r(), v0.g(), v0.b(), 255);
    SDL_RenderDrawLine(renderer.get(), static_cast<int>(v0.position.x()), static_cast<int>(v0.position.y()),
                       static_cast<int>(v1.position.x()), static_cast<int>(v1.position.y()));

    SDL_SetRenderDrawColor(renderer.get(), v1.r(), v1.g(), v1.b(), 255);
    SDL_RenderDrawLine(renderer.get(), static_cast<int>(v1.position.x()), static_cast<int>(v1.position.y()),
                       static_cast<int>(v2.position.x()), static_cast<int>(v2.position.y()));

    SDL_SetRenderDrawColor(renderer.get(), v2.r(), v2.g(), v2.b(), 255);
    SDL_RenderDrawLine(renderer.get(), static_cast<int>(v2.position.x()), static_cast<int>(v2.position.y()),
                       static_cast<int>(v0.position.x()), static_cast<int>(v0.position.y()));
}

void SdlApp::setWindowTitleWithFPS()
{
    std::string title = "My Rasterizer - FPS: " + std::to_string(static_cast<int>(currentFPS));
    SDL_SetWindowTitle(window.get(), title.c_str());
}
