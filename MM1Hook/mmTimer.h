#pragma once

#include "asNode.h"

class mmTimer : public asNode
{
    unsigned int CountDown;
    float DefaultTime;
    float Time;
    unsigned int Running;
};