#ifndef _FRAME_H_
#define _FRAME_H_

#include <Eigen/Dense>

class Frame
{
public:

    enum class Handedness {
        RightHanded,
        LeftHanded
    };

    // 默认构造函数
    Frame();

    // 带参数构造函数
    Frame(const Eigen::Vector3f& xAxis, const Eigen::Vector3f& yAxis, const Eigen::Vector3f& zAxis, const Eigen::Vector3f& origin, Handedness handedness = Handedness::RightHanded);

    // 获取坐标系原点
    const Eigen::Vector3f& origin() const;

    // 获取X、Y、Z轴
    const Eigen::Vector3f& xAxis() const;
    const Eigen::Vector3f& yAxis() const;
    const Eigen::Vector3f& zAxis() const;

    // 获取左右手系标志
    Handedness handedness() const;

    // 局部坐标 -> 世界坐标
    Eigen::Vector3f localToWorld(const Eigen::Vector3f& local) const;

    // 世界坐标 -> 局部坐标
    Eigen::Vector3f worldToLocal(const Eigen::Vector3f& world) const;

private:
    Eigen::Vector3f xAxis_;
    Eigen::Vector3f yAxis_;
    Eigen::Vector3f zAxis_;
    Eigen::Vector3f origin_;
    Handedness handedness_;

    // 检查三个轴是否正交且单位长度
    bool isOrthonormal() const;

    // 检查坐标系的手性（左右手系）
    bool checkHandedness() const;
};

#endif // _FRAME_H_