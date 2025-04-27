#ifndef _FRAME_H_
#define _FRAME_H_

#include <Eigen/Dense>

class Frame
{
public:
    using Vec3 = Eigen::Vector3f;

    enum class Handedness {
        RightHanded,
        LeftHanded
    };

    // 默认构造函数
    Frame();

    // 带参数构造函数
    Frame(const Vec3& xAxis, const Vec3& yAxis, const Vec3& zAxis, const Vec3& origin, Handedness handedness = Handedness::RightHanded);

    // 获取坐标系原点
    const Vec3& origin() const;

    // 获取X、Y、Z轴
    const Vec3& xAxis() const;
    const Vec3& yAxis() const;
    const Vec3& zAxis() const;

    // 获取左右手系标志
    Handedness handedness() const;

    // 局部坐标 -> 世界坐标
    Vec3 localToWorld(const Vec3& local) const;

    // 世界坐标 -> 局部坐标
    Vec3 worldToLocal(const Vec3& world) const;

private:
    Vec3 xAxis_;
    Vec3 yAxis_;
    Vec3 zAxis_;
    Vec3 origin_;
    Handedness handedness_;

    // 检查三个轴是否正交且单位长度
    bool isOrthonormal() const;

    // 检查坐标系的手性（左右手系）
    bool checkHandedness() const;
};

#endif // _FRAME_H_
