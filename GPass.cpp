#include "GPass.h"
#include "CommonFS.h"
#include "CommonVS.h"

GPass::GPass()
{
    vertexShader_ = std::make_unique<CommonVS>();
    fragmentShader_ = std::make_unique<CommonFS>();
}