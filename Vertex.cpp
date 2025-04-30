#include "Vertex.h"


Vertex& Vertex::operator=(const Vertex& other) {
    if (this != &other) {
        position = other.position;
        color = other.color;
        texCoord = other.texCoord;
    }
    return *this;
}
void Vertex::clampColor()
{
    color = color.cwiseMax(Eigen::Vector3f(0.0f, 0.0f, 0.0f));
    color = color.cwiseMin(Eigen::Vector3f(1.0f, 1.0f, 1.0f));
}

uint8_t Vertex::r() const
{
    return static_cast<uint8_t>(color.x() * 255.0f);
}

uint8_t Vertex::g() const
{
    return static_cast<uint8_t>(color.y() * 255.0f);
}

uint8_t Vertex::b() const
{
    return static_cast<uint8_t>(color.z() * 255.0f);
}
