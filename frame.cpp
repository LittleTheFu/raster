#include "Frame.h"
#include <cmath>
#include <cassert>

Frame::Frame()
    : origin_(Eigen::Vector3f::Zero()), handedness_(Handedness::RightHanded)
{
    xAxis_ = Eigen::Vector3f::UnitX();
    yAxis_ = Eigen::Vector3f::UnitY();
    zAxis_ = Eigen::Vector3f::UnitZ();
}

Frame::Frame(const Eigen::Vector3f& xAxis, const Eigen::Vector3f& yAxis, const Eigen::Vector3f& zAxis, const Eigen::Vector3f& origin, Handedness handedness)
    : xAxis_(xAxis), yAxis_(yAxis), zAxis_(zAxis), origin_(origin), handedness_(handedness)
{
    assert(isOrthonormal() && "Axes must be orthonormal!");
    assert(checkHandedness() && "Axes do not match the specified handedness!");
}

const Eigen::Vector3f& Frame::origin() const { return origin_; }

const Eigen::Vector3f& Frame::xAxis() const { return xAxis_; }

const Eigen::Vector3f& Frame::yAxis() const { return yAxis_; }

const Eigen::Vector3f& Frame::zAxis() const { return zAxis_; }

Frame::Handedness Frame::handedness() const { return handedness_; }

Eigen::Vector3f Frame::localToWorld(const Eigen::Vector3f& local) const {
    return xAxis_ * local.x() + yAxis_ * local.y() + zAxis_ * local.z() + origin_;
}

Eigen::Vector3f Frame::worldToLocal(const Eigen::Vector3f& world) const {
    Eigen::Vector3f p = world - origin_;
    return Eigen::Vector3f(xAxis_.dot(p), yAxis_.dot(p), zAxis_.dot(p));
}

bool Frame::isOrthonormal() const {
    constexpr float epsilon = 1e-4f;
    return std::abs(xAxis_.dot(yAxis_)) < epsilon &&
           std::abs(xAxis_.dot(zAxis_)) < epsilon &&
           std::abs(yAxis_.dot(zAxis_)) < epsilon &&
           std::abs(xAxis_.norm() - 1.0f) < epsilon &&
           std::abs(yAxis_.norm() - 1.0f) < epsilon &&
           std::abs(zAxis_.norm() - 1.0f) < epsilon;
}

bool Frame::checkHandedness() const {
    float det = xAxis_.cross(yAxis_).dot(zAxis_);
    if (handedness_ == Handedness::RightHanded) {
        return det > 0.0f;
    } else {
        return det < 0.0f;
    }
}