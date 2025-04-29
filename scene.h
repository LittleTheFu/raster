#ifndef _SCENE_H_
#define _SCENE_H_

#include "camera.h"
#include "triangle.h"
#include <Eigen/Dense>
#include <array>

class Scene
{
public:
    Scene();
    std::array<Eigen::Vector3f, 3> getTriangleScreenCoords() const;

private:
    Eigen::Vector3f ndcToScreen(const Eigen::Vector3f& ndc, int screenWidth = 800, int screenHeight = 600) const;

private:
    Camera camera;
    Triangle triangle;
};

#endif //_SCENE_H_