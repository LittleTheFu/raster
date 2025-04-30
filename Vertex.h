#ifndef _VERTEX_H_
#define _VERTEX_H_

#include <Eigen/Dense>


class Vertex {
public:
    void clampColor(); // 限制颜色范围在0-1之间
    
public:
    Eigen::Vector4f position;
    Eigen::Vector3f color; // 法线
};

#endif // _VERTEX_H_