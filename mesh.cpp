#include "mesh.h"

#include <assimp/Importer.hpp>  // C++ importer interface
#include <assimp/scene.h>       // Output data structure
#include <assimp/postprocess.h> // Post processing flags
#include <iostream>

Mesh::Mesh(const std::string fileName)
{
    Assimp::Importer importer;

    const aiScene *scene = importer.ReadFile(fileName.c_str(), aiProcess_Triangulate);
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        std::cerr << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
        return;
    }
    int faceNUM = scene->mMeshes[0]->mNumFaces;
    std::cout << "face num : " << faceNUM << std::endl;
    for(int i = 0; i < faceNUM; i++)
    {
        aiFace face = scene->mMeshes[0]->mFaces[i];
        assert(face.mNumIndices == 3);

        Vertex va = createTriVertex(scene->mMeshes[0], face.mIndices[0]);
        Vertex vb = createTriVertex(scene->mMeshes[0], face.mIndices[1]);
        Vertex vc = createTriVertex(scene->mMeshes[0], face.mIndices[2]);

        vertices.push_back(va);
        vertices.push_back(vb);
        vertices.push_back(vc);
    }
}

const std::vector<Vertex>& Mesh::getVertices() const
{
    return vertices;
}

// std::vector<Vertex>& Mesh::getVertices()
// {
//     return vertices;
// }

Vertex Mesh::createTriVertex(const aiMesh *mesh, unsigned int index) const
{
    float x = mesh->mVertices[index].x;
    float y = mesh->mVertices[index].y;
    float z = mesh->mVertices[index].z;

    float nx = mesh->mNormals[index].x;
    float ny = mesh->mNormals[index].y;
    float nz = mesh->mNormals[index].z;

    float u = mesh->mTextureCoords[0][index].x;
    float v = mesh->mTextureCoords[0][index].y;

    Vertex vertex{Eigen::Vector4f(x, y, z, 1.0f),
                  Eigen::Vector3f(1.0f, 1.0f, 1.0f),
                  Eigen::Vector2f(u, v),
                  Eigen::Vector3f(nx, ny, nz)};

    return vertex;
}