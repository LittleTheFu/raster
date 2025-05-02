#include "Vertex.h"
#include <cmath>

Vertex& Vertex::operator=(const Vertex& other) {
    if (this != &other) {
        position = other.position;
        color = other.color;
        texCoord = other.texCoord;
        normal = other.normal;
        viewDir = other.viewDir;
        worldPosition = other.worldPosition;
    }
    return *this;
}

Vertex Vertex::interpolate(const Vertex &other, float t) const
{
    Vertex result;

    if (t < 0.0f) return *this;
    if (t > 1.0f) return other;

    result.position = (1.0f - t) * position + t * other.position;
    result.color = (1.0f - t) * color + t * other.color;
    result.texCoord = (1.0f - t) * texCoord + t * other.texCoord;
    result.normal = (1.0f - t) * normal + t * other.normal;
    result.viewDir = ((1.0f - t) * viewDir + t * other.viewDir).normalized();
    result.worldPosition = (1.0f - t) * worldPosition + t * other.worldPosition;

    return result;
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