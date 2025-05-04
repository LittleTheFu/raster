#ifndef _SHADOW_PASS_H_
#define _SHADOW_PASS_H_

#include "pass.h"
#include "zbuffer.h"

class ShadowPass : public Pass
{
public:
    ShadowPass(int width, int height);

    virtual void preRun() override;
    const std::shared_ptr<ZBuffer> &getZBuffer() const;

private:
    std::shared_ptr<ZBuffer> zBuffer;
};

#endif