#ifndef _SCENE_H_
#define _SCENE_H_

#include "camera.h"
#include "triangle.h"
#include "pipeline.h"
#include "vertexBuffer.h"
#include "Vertex.h"
#include "mesh.h"
#include "light.h"
#include "frameBuffer.h"
#include "texture.h"
#include <Eigen/Dense>
#include <vector>

class Scene
{
public:
    Scene(int width, int height);
    std::vector<Vertex> applyVertexShader();
    const Light& getLight() const;
    const FrameBuffer& getFrameBuffer() const;

    void run();


private:
    Texture texture; // 纹理对象
    Light light; // 光源对象
    Camera camera;
    VertexBuffer vertexBuffer; // 顶点缓冲区
    Mesh mesh; // 网格对象
    FrameBuffer frameBuffer; // 帧缓冲区对象
    Pipeline pipeline;
};

#endif //_SCENE_H_