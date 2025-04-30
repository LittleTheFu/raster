#ifndef _VERTEX_BUFFER_H_
#define _VERTEX_BUFFER_H_

#include <vector>

class VertexBuffer {
public:
    const std::vector<float>& getVertices() const;
        
private:
    std::vector<float> vertices;
};

#endif