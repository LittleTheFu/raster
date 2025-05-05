#ifndef _BOX_H_
#define _BOX_H_ 

#include "Vertex.h"
#include <array>

class Box
{
public:
	Box(float scale = 1.0f);

    const std::array<Vertex, 36> &getVertices() const;
    void flipNormals();

private:
    void init(float scale);

private:
    std::array<Vertex, 36> m_vertices;
};

#endif