#pragma once

#include "agiRefreshable.h"
#include "Vector.h"

class agiLightParameters
{
public:
    unsigned int dword0;
    unsigned int dword4;
    unsigned int dword8;
    unsigned int dwordC;
    unsigned int dword10;
    float float14;
    float float18;
    float float1C;
    float float20;
    float float24;
    float float28;
    float float2C;
    float float30;
    float float34;
    Vector4 vector38;
    unsigned int dword48;
    unsigned int dword4C;
    float float50;
    unsigned int dword54;
    float float58;
    float float5C;
    unsigned int dword60;
    unsigned int dword64;
    unsigned int dword68;
    unsigned int dword6C;
};

class agiLight : public agiRefreshable
{
public:
    agiLightParameters Parameters;

    virtual int Update(void) = 0;
    virtual void Remove(void) = 0;
};

class agiD3DLight : public agiLight
{
    unsigned int dword88;
};
