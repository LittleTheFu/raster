#ifndef _LIGHT_H_
#define _LIGHT_H_

#include <Eigen/Dense>


class Light
{
public:
    Eigen::Vector3f position; // 光源位置
    Eigen::Vector3f color;    // 光源颜色
    Eigen::Vector3f intensity; // 光源强度
};

#endif// _LIGHT_H_