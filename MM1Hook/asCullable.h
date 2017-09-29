#pragma once

#include "Base.h"

class asCullable : public Base
{
    virtual void Cull(void) = 0;
};
