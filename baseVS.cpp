#include "baseVS.h"

void BaseVS::setMvpMatrix(const Eigen::Matrix4f &mvpMatrix)
{
    mvpMatrix_ = mvpMatrix;
}

const Eigen::Matrix4f &BaseVS::getMvpMatrix() const
{
    return mvpMatrix_;
}