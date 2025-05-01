#ifndef _SCENE_H_
#define _SCENE_H_

#include "camera.h"
#include "triangle.h"
#include "pipeline.h"
#include "vertexBuffer.h"
#include "Vertex.h"
#include "mesh.h"
#include "light.h"
#include <Eigen/Dense>
#include <vector>

class Scene
{
public:
    Scene(int width, int height);
    std::vector<Vertex> getTriangleScreenCoords();
    const Light& getLight() const;

private:
    Camera camera;
    Pipeline pipeline;
    VertexBuffer vertexBuffer; // 顶点缓冲区
    Mesh mesh; // 网格对象
    Light light; // 光源对象
    
};

#endif //_SCENE_H_