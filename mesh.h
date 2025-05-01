#ifndef _MESH_H_
#define _MESH_H_

#include <assimp/mesh.h>

#include <string>
#include <vector>
#include "Vertex.h"

class Mesh {
public:
    Mesh(const std::string fileName);

    const std::vector<Vertex>& getVertices() const;
    // std::vector<Vertex>& getVertices();

private:
    Vertex createTriVertex(const aiMesh* mesh, unsigned int index) const;

private:
    std::vector<Vertex> vertices;
};

#endif // _MESH_H_