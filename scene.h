#ifndef _SCENE_H_
#define _SCENE_H_

#include "camera.h"
#include "triangle.h"
#include "pipeline.h"
#include <Eigen/Dense>
#include <array>

class Scene
{
public:
    Scene();
    std::array<Eigen::Vector3f, 3> getTriangleScreenCoords();

private:
    Eigen::Vector3f ndcToScreen(const Eigen::Vector4f& ndc, int screenWidth = 800, int screenHeight = 600) const;

private:
    Camera camera;
    Triangle triangle;
    Pipeline pipeline;
};

#endif //_SCENE_H_