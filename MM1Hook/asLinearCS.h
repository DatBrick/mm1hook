#pragma once

#include "asNode.h"
#include "Vector.h"

class asLinearCS : public asNode
{
public:
    Matrix34 matrix341C;
    Matrix34 matrix344C;
    int Global;
    asLinearCS *Parent;
};
