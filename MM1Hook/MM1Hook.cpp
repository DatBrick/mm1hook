#include "stdafx.h"
#include "Hooking.h"

#include "FileSystem.h"

#include "MM1Hook.h"

#include "Vector.h"

#include "MetaClass.h"

namespace MM1
{
    auto OpenFile = get_as<class Stream* (*)(const char *name, const char *folder, const char *extension, int a4, int a5, const char *type)>(0x5418E0);
    auto fgets = get_as<int (*)(char *, int, class Stream *)>(0x540F60);

    auto malloc = get_as<void*(*)(unsigned int)>(0x50F560);
    auto free   = get_as<void(*)(void*)>(0x50F580);
}

class WArray
{
public:
    void Read(const char* name)
    {
        auto WArray__AddWidgetData = get_as<void (WArray::*)(int, int, const Vector4 &, char *)>(0x4A1100);

        if (Stream* pStream = MM1::OpenFile(name, "tune", ".csv", 0, 0, "widget file"))
        {
            char line[128];

            MM1::fgets(line, 128, pStream);

            while ( MM1::fgets(line, 128, pStream) )
            {
#pragma warning(push)
#pragma warning(disable : 4996)

                auto menuName = strtok(line, ",");
                auto menuID = atoi(strtok(0, ","));

                auto widgetName = strtok(0, ",");
                auto widgetID = atoi(strtok(0, ","));

                Vector4 dimensions;
                dimensions.w = (float) atoi(strtok(0, ",")) / 640;
                dimensions.x = (float) atoi(strtok(0, ",")) / 480;
                dimensions.y = (float) atoi(strtok(0, ",")) / 640;
                dimensions.z = (float) atoi(strtok(0, ",")) / 480;

                auto description = strtok(0, "\r\n");

#pragma warning(pop)

                (this->*WArray__AddWidgetData)(menuID, widgetID, dimensions, description);
            }

            pStream->Destructor(1);
        }
        else
        {
            // Errorf("Can't open widget data file '%s'", name);
        }
    }
};


FunctionHook<void (WArray::*)(const char*)> Read(0x4A0F20, &WArray::Read);

bool dumped = false;

decltype(Hook_ChangeDisplaySettingsA) Hook_ChangeDisplaySettingsA((std::uintptr_t) &ChangeDisplaySettingsA, [ ] (DEVMODEA* lpDevMode, DWORD dwFlags) -> LONG
{
    if (!dumped)
    {
        dumped = true;

        DumpMetaInfo();
    }

    if (lpDevMode)
    {
        lpDevMode->dmPelsWidth = 0;
        lpDevMode->dmPelsHeight = 0;
    }

    return Hook_ChangeDisplaySettingsA(lpDevMode, dwFlags);
});

#include <fstream>
#include <algorithm>
#include <string>

std::string GetMetaTypeName(MetaType* pType)
{
    switch (*(std::uintptr_t*)(pType))
    {
        case 0x5960C8: return "Vector3";
        case 0x5960F8: return "Vector4";
        case 0x596218: return "Vector2";
        case 0x5962D8: return "Char";
        case 0x5962F0: return "SignedChar";
        case 0x596308: return "UnsignedChar";
        case 0x596320: return "SignedShort";
        case 0x596338: return "UnsignedShort";
        case 0x596350: return "SignedInt";
        case 0x596368: return "SignedInt64";
        case 0x596380: return "UnsignedInt";
        case 0x596398: return "Float";
        case 0x5963B0: return "String";

        case 0x590F58:
        {
            return static_cast<StructType*>(pType)->pMetaClass->Name;
        }

        case 0x590FB8:
        {
            auto* pArrayOfType = static_cast<ArrayOfType*>(pType);
            
            return GetMetaTypeName(pArrayOfType->pType) + "[" + std::to_string(pArrayOfType->nCount) + "]"; 
        }

        case 0x5942A8:
        {
            auto* pRefToType = static_cast<RefToType*>(pType);

            return GetMetaTypeName(pRefToType->pType) + "& (" + std::to_string(pRefToType->RefOffset) + "," + std::to_string(pRefToType->RefSize) + ")";
        }

        case 0x5953E0:
        {
            auto* pPtrToType = static_cast<PtrToType*>(pType);
        
            return GetMetaTypeName(pPtrToType->pType) + "*";
        }
    }

    return "field";
}

void DumpMetaInfo()
{
    std::FILE* output = std::fopen("meta.txt", "w");

    auto& classes = get_ref<MetaClass*[256]>(0x711B44);
    auto& count   = get_ref<int>(0x711B38);

    auto& pCurrent = get_ref<MetaClass*>(0x711F40);
    auto& ppField  = get_ref<MetaField**>(0x711F44);

    std::fprintf(output, "Total: %i\n", count);

    std::fflush(output);

    for (int i = 0; i < count; ++i)
    {
        auto* pClass = classes[i];

        std::fprintf(output, "%s (%u)", pClass->Name, pClass->Size);

        if (pClass->Parent)
        {
            std::fprintf(output, " : %s (%u)", pClass->Parent->Name, pClass->Parent->Size);
        }

        std::putc('\n', output);

        if (pClass->DeclareFields)
        {
            if (!pClass->pFields)
            {
                pCurrent = pClass;
                ppField = &pClass->pFields;

                pClass->DeclareFields();
            }

            MetaField* fields[256];
            std::size_t field_count = 0;

            for (auto* pField = pClass->pFields; pField; pField = pField->Next)
            {
                if (pClass->Parent && (pField->Offset < pClass->Parent->Size))
                    continue;

                fields[field_count++] = pField;
            }

            std::sort(fields, fields + field_count, [ ] (MetaField* lhs, MetaField* rhs)
            {
                return lhs->Offset < rhs->Offset;
            });

            for (std::size_t j = 0; j < field_count; ++j)
            {
                auto* pField = fields[j];
                auto* pType  = pField->pType;

                std::fprintf(output, "%s (%u)", GetMetaTypeName(pType).c_str(), pType->SizeOf());     

                std::fprintf(output, " @ 0x%-4X: %s\n", pField->Offset, pField->Name);
                std::fflush(output);
            }
        }

        std::putc('\n', output);

        std::fflush(output);
    }

    std::fflush(output);
    std::fclose(output);
}