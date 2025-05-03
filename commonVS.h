#ifndef _COMMON_VS_H_
#define _COMMON_VS_H_

#include "baseVS.h"

class CommonVS : public BaseVS
{
    public:
        Vertex apply(const Vertex& vertex) const override;
};

#endif // _COMMON_VS_H_