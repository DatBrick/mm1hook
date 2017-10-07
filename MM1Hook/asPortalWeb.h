#pragma once

#include "asNode.h"

class asPortalWeb : public asNode
{
public:
    char pad0[34856];

    virtual struct asPortalCell * GetStartCell(class Vector3 &,struct asPortalCell *,class mmPolygon * *) = 0;
};