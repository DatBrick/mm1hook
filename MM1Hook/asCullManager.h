#pragma once

#include "asNode.h"

class asCullManager : public asNode
{
public:
    // TODO

    virtual void DeclareCamera(class asCamera *) = 0;
    virtual void DeclareCullable(class asCullable *) = 0;
    virtual void DeclareCullable2D(class asCullable *) = 0;
};
