#include "SdlApp.h"

SdlApp::SdlApp(const std::string &title, int width, int height)
    : scene(width, height),zBuffer(width, height)
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
    // 更新 Z-buffer
    zBuffer.clear();
    
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
    // 对顶点按 y 坐标排序，确保 v0 是顶部，v2 是底部
    std::array<Vertex, 3> vertices = {v0, v1, v2};
    std::sort(vertices.begin(), vertices.end(), [](const Vertex &a, const Vertex &b)
              {
                  return a.position.y() < b.position.y(); // 从上到下排序
              });

    // 获取排序后的顶点
    const Vertex &top = vertices[0];
    const Vertex &middle = vertices[1];
    const Vertex &bottom = vertices[2];

    // 扫描线填充算法
    for (int y = static_cast<int>(top.position.y()); y <= static_cast<int>(bottom.position.y()); ++y)
    {
        // 计算当前扫描线的左右交点
        float leftX = 0.0f, rightX = 0.0f;
        Eigen::Vector3f leftColor, rightColor;
        float leftZ, rightZ;

        // 对于扫描线在顶点与中间点之间
        if (y <= middle.position.y())
        {
            // 计算与 top 和 middle 之间的交点
            leftX = interpolateX(top, middle, y, leftColor, leftZ);
            rightX = interpolateX(top, bottom, y, rightColor, rightZ);
        }
        else
        {
            // 计算与 middle 和 bottom 之间的交点
            leftX = interpolateX(middle, bottom, y, leftColor, leftZ);
            rightX = interpolateX(top, bottom, y, rightColor, rightZ);
        }

        // 对交点进行排序，以确保从左到右绘制
        if (leftX > rightX)
        {
            std::swap(leftX, rightX);
            std::swap(leftColor, rightColor);
            std::swap(leftZ, rightZ);
        }

        // 在当前扫描线填充颜色
        for (int x = static_cast<int>(leftX); x <= static_cast<int>(rightX); ++x)
        {
            // 使用左右交点的颜色进行插值
            float alpha = (x - leftX) / (rightX - leftX);
            Eigen::Vector3f interpolatedColor = (1 - alpha) * leftColor + alpha * rightColor;
            float interpolatedZ = (1 - alpha) * leftZ + alpha * rightZ; // 插值 z 值

            // 更新 Z-buffer，只有在深度值更小的情况下才绘制像素
            if (!zBuffer.testAndUpdate(x, y, interpolatedZ))
            {
                continue; // 如果 Z-buffer 更新失败，则跳过绘制
            }

            // 使用插值后的颜色设置绘制颜色
            SDL_SetRenderDrawColor(renderer.get(),
                                   static_cast<uint8_t>(interpolatedColor.x() * 255.0f),
                                   static_cast<uint8_t>(interpolatedColor.y() * 255.0f),
                                   static_cast<uint8_t>(interpolatedColor.z() * 255.0f),
                                   255);               // 设置填充颜色
            SDL_RenderDrawPoint(renderer.get(), x, y); // 绘制像素
        }
    }
}

// 计算给定 y 值的交点，同时返回颜色的插值
float SdlApp::interpolateX(const Vertex &v0, const Vertex &v1, int y, Eigen::Vector3f &color, float& z) const
{
    if (v0.position.y() == v1.position.y())
    {
        color = v0.color; // 如果两个点的 y 相同，直接返回 x 和颜色
        return v0.position.x();
    }

    // 计算线性插值的比例 t
    float t = (y - v0.position.y()) / (v1.position.y() - v0.position.y());
    float x = v0.position.x() + t * (v1.position.x() - v0.position.x());

    // 计算颜色的插值
    color = (1 - t) * v0.color + t * v1.color;
    z = (1 - t) * v0.position.z() + t * v1.position.z(); // 计算 z 值的插值

    return x;
}

void SdlApp::setWindowTitleWithFPS()
{
    std::string title = "My Rasterizer - FPS: " + std::to_string(static_cast<int>(currentFPS));
    SDL_SetWindowTitle(window.get(), title.c_str());
}
