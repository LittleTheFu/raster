#ifndef COMMONFS_H
#define COMMONFS_H

#include "baseFS.h"
#include "gBufferData.h"
#include <Eigen/Dense>

class CommonFS : public BaseFS
{
public:
    virtual void apply(const Vertex &vertex) override;

    virtual void setGBufferData(const std::shared_ptr<GBufferData>& gBufferData) override; // 设置GBuffer数据
    virtual void setHeight(int height) override;
    virtual void setWidth(int width) override;

private:
    std::shared_ptr<GBufferData> gBufferData_; // GBuffer数据

    int width_;
    int height_;
};

#endif // COMMONFS_H