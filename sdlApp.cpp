#include "SdlApp.h"

SdlApp::SdlApp(const std::string &title, int width, int height)
    : scene(width, height),
      zBuffer(width, height),
      texture("lena.png")
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

    // SDL_RenderDrawPoint(renderer.get(), v0.position.x(), v0.position.y());
    // SDL_RenderDrawPoint(renderer.get(), v1.position.x(), v1.position.y());
    // SDL_RenderDrawPoint(renderer.get(), v2.position.x(), v2.position.y());

    // SDL_RenderDrawLine(renderer.get(), v0.position.x(), v0.position.y(), v1.position.x(), v1.position.y());
    // SDL_RenderDrawLine(renderer.get(), v1.position.x(), v1.position.y(), v2.position.x(), v2.position.y());
    // SDL_RenderDrawLine(renderer.get(), v2.position.x(), v2.position.y(), v0.position.x(), v0.position.y());

    // return ; // 仅绘制顶点
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
        Vertex leftVertex, rightVertex;

        // 对于扫描线在顶点与中间点之间
        if (y <= middle.position.y())
        {
            // 计算与 top 和 middle 之间的交点
            leftVertex = interpolateVertex(top, middle, y);
            rightVertex = interpolateVertex(top, bottom, y);
        }
        else
        {
            // 计算与 middle 和 bottom 之间的交点
            leftVertex = interpolateVertex(middle, bottom, y);
            rightVertex = interpolateVertex(top, bottom, y);
        }

        // 对交点进行排序，以确保从左到右绘制
        if (leftVertex.position.x() > rightVertex.position.x())
        {
            std::swap(leftVertex, rightVertex);
        }

        if(leftVertex.position.x() < 20)
        {
            std::cout << "leftVertex.position.x() < 20" << std::endl;
        }

        // 在当前扫描线填充颜色
        for (int x = static_cast<int>(leftVertex.position.x() + 0.5f); x <= static_cast<int>(rightVertex.position.x() + 0.5f); ++x)
        {
            // 使用左右交点的颜色进行插值
            float alpha = (x - leftVertex.position.x()) / (rightVertex.position.x() - leftVertex.position.x());
            Eigen::Vector3f interpolatedColor = (1 - alpha) * leftVertex.color + alpha * rightVertex.color;
            // 插值纹理坐标
            Eigen::Vector2f interpolatedTexCoord = (1 - alpha) * leftVertex.texCoord + alpha * rightVertex.texCoord;
            float interpolatedZ = (1 - alpha) * leftVertex.position.z() + alpha * rightVertex.position.z(); // 插值 z 值

            // 更新 Z-buffer，只有在深度值更小的情况下才绘制像素
            if (!zBuffer.testAndUpdate(x, y, interpolatedZ))
            {
                continue; // 如果 Z-buffer 更新失败，则跳过绘制
            }

            uint8_t r,g,b;
            texture.getColor(interpolatedTexCoord.x(), interpolatedTexCoord.y(), r, g, b);

            // r = interpolatedTexCoord.x() * 255;
            // g = interpolatedTexCoord.y() * 255;
            // b = 0;

            // 使用插值后的颜色设置绘制颜色
            SDL_SetRenderDrawColor(renderer.get(), r, g, b, 255); // 设置填充颜色
            SDL_RenderDrawPoint(renderer.get(), x, y); // 绘制像素
        }
    }
}


// 计算给定 y 值的交点，同时返回颜色的插值
Vertex SdlApp::interpolateVertex(const Vertex &v0, const Vertex &v1, int y) const
{
    Vertex result;

    // if (v0.position.y() - v1.position.y() < 0.01f)
    // {
    //     result = v0; // 如果y值相同，直接返回v0
    //     return result;
    // }

    // if (v1.position.y() - v0.position.y() < 0.01f)
    // {
    //     result = v0; // 如果y值相同，直接返回v0
    //     return result;
    // }

    // 计算插值比例t
    float t = (y - v0.position.y()) / (v1.position.y() - v0.position.y());

    if(t < 0 || t > 1)
    {
        result = v0; // 如果t不在[0,1]范围内，直接返回v0
        return result;
    }

    // 插值位置
    result.position.x() = v0.position.x() + t * (v1.position.x() - v0.position.x());
    result.position.y() = y;  // 固定y
    result.position.z() = v0.position.z() + t * (v1.position.z() - v0.position.z());
    result.position.w() = 1.0f;  // 假设使用齐次坐标

    // 插值颜色
    result.color = (1 - t) * v0.color + t * v1.color;

    // 插值纹理坐标
    result.texCoord = (1 - t) * v0.texCoord + t * v1.texCoord;

    if(result.position.x() < 20)
    {
        std::cout << "result.position.x() < 20" << std::endl;
    }

    return result;
}


void SdlApp::setWindowTitleWithFPS()
{
    std::string title = "My Rasterizer - FPS: " + std::to_string(static_cast<int>(currentFPS));
    SDL_SetWindowTitle(window.get(), title.c_str());
}
