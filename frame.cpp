#include "Frame.h"
#include <cmath>
#include <cassert>

Frame::Frame()
    : origin_(Vec3::Zero()), handedness_(Handedness::RightHanded)
{
    xAxis_ = Vec3::UnitX();
    yAxis_ = Vec3::UnitY();
    zAxis_ = Vec3::UnitZ();
}

Frame::Frame(const Vec3& xAxis, const Vec3& yAxis, const Vec3& zAxis, const Vec3& origin, Handedness handedness)
    : xAxis_(xAxis), yAxis_(yAxis), zAxis_(zAxis), origin_(origin), handedness_(handedness)
{
    assert(isOrthonormal() && "Axes must be orthonormal!");
    assert(checkHandedness() && "Axes do not match the specified handedness!");
}

const Frame::Vec3& Frame::origin() const { return origin_; }

const Frame::Vec3& Frame::xAxis() const { return xAxis_; }

const Frame::Vec3& Frame::yAxis() const { return yAxis_; }

const Frame::Vec3& Frame::zAxis() const { return zAxis_; }

Frame::Handedness Frame::handedness() const { return handedness_; }

Frame::Vec3 Frame::localToWorld(const Frame::Vec3& local) const {
    return xAxis_ * local.x() + yAxis_ * local.y() + zAxis_ * local.z() + origin_;
}

Frame::Vec3 Frame::worldToLocal(const Frame::Vec3& world) const {
    Vec3 p = world - origin_;
    return Vec3(xAxis_.dot(p), yAxis_.dot(p), zAxis_.dot(p));
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
