#ifndef _SHADOW_MAP_CAMERA_H_
#define _SHADOW_MAP_CAMERA_H_

#include "camera.h"
#include <array>
#include <Eigen/Dense>
#include "zbuffer.h"

class ShadowMapCamera
{
public:
    static const int CAMERA_NUM = 6;

    enum CameraType
    {
        LEFT = 0,
        RIGHT,
        TOP,
        BOTTOM,
        FRONT,
        BACK
    };

public:
    ShadowMapCamera();
    void setPosition(const Eigen::Vector3f& position);

    void clearZBuffers();

private:
    std::array<Camera, CAMERA_NUM> cameras;
    std::array<ZBuffer, CAMERA_NUM> zBuffers;
};

#endif