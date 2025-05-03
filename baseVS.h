#ifndef _BASE_FS_H_
#define _BASE_FS_H_

#include <Eigen/Dense>
#include "Vertex.h"

class BaseVS
{
public:
    virtual Vertex apply(const Vertex& vertex) const = 0;

    void setMvpMatrix(const Eigen::Matrix4f& mvpMatrix);
    const Eigen::Matrix4f& getMvpMatrix() const;

private:
    Eigen::Matrix4f mvpMatrix_;
};

#endif