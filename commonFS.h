#ifndef COMMONFS_H
#define COMMONFS_H

#include "baseFS.h"
#include "gBufferData.h"
#include <Eigen/Dense>

class CommonFS : public BaseFS
{
public:
    void apply(const Vertex &vertex) override;
    void setGBufferData(std::shared_ptr<GBufferData> gBufferData);

private:
    std::shared_ptr<GBufferData> gBufferData_; // GBuffer数据
};

#endif // COMMONFS_H