#ifndef _SHAODOW_MAP_FS_H_
#define _SHAODOW_MAP_FS_H_

#include <Eigen/Dense>
#include "zbuffer.h"
#include "vertex.h"

class ShadowMapFS
{
public:
    ShadowMapFS(ZBuffer& zBuffer);

    void apply(const Vertex& vertex);
    void setZBuffer(std::shared_ptr<ZBuffer> zBuffer);

private:
    std::shared_ptr<ZBuffer> zBuffer_; // 深度缓冲区对象
};

#endif // _SHAODOW_MAP_FS_H_