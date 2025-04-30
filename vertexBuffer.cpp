#include "vertexBuffer.h"

const std::vector<Vertex>& VertexBuffer::getVertices() const
{
    return vertices;
}

void VertexBuffer::addVertex(const Vertex &vertex)
{
    vertices.push_back(vertex);
}
