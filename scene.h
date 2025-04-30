#ifndef _SCENE_H_
#define _SCENE_H_

#include "camera.h"
#include "triangle.h"
#include "pipeline.h"
#include "vertexBuffer.h"
#include "Vertex.h"
#include <Eigen/Dense>
#include <vector>

class Scene
{
public:
    Scene(int width, int height);
    std::vector<Vertex> getTriangleScreenCoords();

private:
    Camera camera;
    Pipeline pipeline;
    VertexBuffer vertexBuffer; // 顶点缓冲区
};

#endif //_SCENE_H_