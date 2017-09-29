#include "stdafx.h"
#include "Hooking.h"

#include "FileSystem.h"

#include "MM1Hook.h"

#include "Vector.h"

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

FunctionHook<LONG (WINAPI*)(DEVMODEA *, DWORD)> Hook_ChangeDisplaySettingsA((std::uintptr_t) &ChangeDisplaySettingsA, [ ] (DEVMODEA* lpDevMode, DWORD dwFlags) -> LONG
{
    if (lpDevMode)
    {
        lpDevMode->dmPelsWidth = 0;
        lpDevMode->dmPelsHeight = 0;
    }

    return Hook_ChangeDisplaySettingsA(lpDevMode, dwFlags);
});

