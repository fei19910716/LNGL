#pragma once

#include <string>
#include "base/shader_cf.h"

class Renderer
{
    public:

    virtual void init() = 0;
    virtual void render() = 0;

};