#ifndef _MESH_H_
#define _MESH_H_

#include <assimp/mesh.h>

#include <string>
#include <vector>
#include "Vertex.h"

class Mesh {
public:
    Mesh(const std::string fileName, float scale = 1.0f, bool flipNormals = false);

    const std::vector<Vertex>& getVertices() const;
    // std::vector<Vertex>& getVertices();

private:
    Vertex createTriVertex(const aiMesh* mesh, unsigned int index) const;

private:
    std::vector<Vertex> vertices;
    float scale_;
    bool flipNormals_;
};

#endif // _MESH_H_