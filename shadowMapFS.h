#ifndef _SHAODOW_MAP_FS_H_
#define _SHAODOW_MAP_FS_H_

#include <Eigen/Dense>
#include "zbuffer.h"
#include "vertex.h"
#include "baseFS.h"

class ShadowMapFS : public BaseFS
{
public:
    void apply(const Vertex& vertex);
    virtual void setShadowZBuffer(const std::shared_ptr<ZBuffer>& zBuffer) override;

private:
    std::shared_ptr<ZBuffer> zBuffer_; // 深度缓冲区对象
};

#endif // _SHAODOW_MAP_FS_H_