#pragma once

#include "asCullable.h"

class asNode : public asCullable
{
public:
    asNode *NextNode;
    asNode *ChildNode;
    asNode *ParentNode;
    const char *Name;
    unsigned int Flags;
    unsigned int dword18;

    virtual void Update(void) = 0;
    virtual void Reset(void) = 0;
    virtual void ResChange(int,int) = 0;
    virtual void UpdatePaused(void) = 0;
    virtual void Load(void) = 0;
    virtual void Save(void) = 0;
};

class asLinearCS : public asNode
{
public:
    Matrix34 matrix341C;
    Matrix34 matrix344C;
    int Global;
    asLinearCS *Parent;
};