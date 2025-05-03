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

private:
    std::shared_ptr<GBufferData> gBufferData_; // GBuffer数据
};

#endif // COMMONFS_H