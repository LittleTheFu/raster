#ifndef _SCREEN_VS_H_
#define _SCREEN_VS_H_ 

#include "baseVS.h"

class ScreenVS : public BaseVS {
public:
    virtual Vertex apply(const Vertex& vertex) const override;
};

#endif// _SCREEN_VS_H_