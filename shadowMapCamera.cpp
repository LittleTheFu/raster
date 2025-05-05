#include "shadowMapCamera.h"

// ShadowMapCamera.cpp
#include "ShadowMapCamera.h"

ShadowMapCamera::ShadowMapCamera()
{
}

void ShadowMapCamera::setPosition(const Eigen::Vector3f &position)
{
    Eigen::Vector3f targets[CAMERA_NUM] = {
        {1.0f, 0.0f, 0.0f},  // LEFT
        {-1.0f, 0.0f, 0.0f}, // RIGHT
        {0.0f, 1.0f, 0.0f},  // TOP
        {0.0f, -1.0f, 0.0f}, // BOTTOM
        {0.0f, 0.0f, 1.0f},  // FRONT
        {0.0f, 0.0f, -1.0f}  // BACK
    };

    Eigen::Vector3f ups[CAMERA_NUM] = {
        {0.0f, 1.0f, 0.0f},  // LEFT (+X朝向，+Y为上)
        {0.0f, 1.0f, 0.0f},  // RIGHT (-X朝向，+Y为上)
        {0.0f, 0.0f, -1.0f}, // TOP (+Y朝向，-Z为上，或者根据你的坐标系可能是+Z)
        {0.0f, 0.0f, 1.0f},  // BOTTOM (-Y朝向，+Z为上，或者根据你的坐标系可能是-Z)
        {0.0f, 1.0f, 0.0f},  // FRONT (+Z朝向，+Y为上)
        {0.0f, 1.0f, 0.0f}   // BACK (-Z朝向，+Y为上)
    };

    for (int i = 0; i < CAMERA_NUM; ++i)
    {
        cameras[i].setPosition(position);
        cameras[i].setTarget(position + targets[i]);
        cameras[i].setUpDirection(ups[i]);
    }
}

void ShadowMapCamera::clearZBuffers()
{
    for(auto& zBuffer : zBuffers)
    {
        zBuffer.clear();
    }
}