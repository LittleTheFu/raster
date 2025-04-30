#include "Vertex.h"

void Vertex::clampColor()
{
    color = color.cwiseMax(Eigen::Vector3f(0.0f, 0.0f, 0.0f));
    color = color.cwiseMin(Eigen::Vector3f(1.0f, 1.0f, 1.0f));
}