#ifndef _VERTEX_BUFFER_H_
#define _VERTEX_BUFFER_H_

#include <vector>
#include "Vertex.h"

class VertexBuffer {
public:
    const std::vector<Vertex>& getVertices() const;
    
    void addVertex(const Vertex& vertex);
        
private:
    std::vector<Vertex> vertices;
};

#endif