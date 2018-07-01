#pragma once

#include "HashTable.h"

#define agiLibMax 2048;

/*
    0x7024D8 | agiLib<agiPhysParameters,agiPhysDef> agiPhysLib;	
    0x706668 | agiLib<agiTexParameters,agiTexDef> agiTexLib;	
    0x70A6C0 | agiLib<agiMtlParameters,agiMtlDef> agiMtlLib;	
*/

template <typename TParams, typename TDefs>
struct agiLib
{
    TParams *Parameters[agiLibMax];
    TDefs *Defs[agiLibMax];
    HashTable LookupTable;
    char gap400C[4];
    int Count;
};