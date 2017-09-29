#include "stdafx.h"
#include "Hooking.h"

#include "Detours\detours.h"
#pragma comment (lib, "Detours\\detours.lib")

bool DetourHook::Hook(void* pFunc, void* pDetour)
{
    _pFunc   = pFunc;
    _pDetour = pDetour;

    DetourTransactionBegin();

    DetourAttach(&_pFunc, _pDetour);

    return DetourTransactionCommit() == NO_ERROR;
}

bool DetourHook::UnHook()
{
    DetourTransactionBegin();

    DetourDetach(&_pFunc, _pDetour);

    return DetourTransactionCommit() == NO_ERROR;
}

HMODULE LoadSystemLibrary(LPCSTR lpLibFileName)
{
    char szDllFile[MAX_PATH];

    GetSystemDirectoryA(szDllFile, sizeof(szDllFile));

    std::snprintf(szDllFile, MAX_PATH, "%s\\%s", szDllFile, lpLibFileName);

    return LoadLibraryA(szDllFile);
}

FARPROC lpDirectInputCreate = nullptr;

#pragma comment(linker, "/EXPORT:DirectInputCreateA=_DirectInputCreate_Impl@16")
#pragma comment(linker, "/EXPORT:DirectInputCreateW=_DirectInputCreate_Impl@16")
EXTERN_C HRESULT WINAPI DirectInputCreate_Impl(HINSTANCE hinst, DWORD dwVersion, LPVOID* lplpDirectInput, LPVOID punkOuter)
{
    if (lpDirectInputCreate == nullptr)
    {
        lpDirectInputCreate = GetProcAddress(LoadSystemLibrary("dinput.dll"), "DirectInputCreateA");

        if (lpDirectInputCreate == nullptr)
        {
            MessageBoxA(NULL, "Failed to find DirectInputCreateA", "ERROR", MB_OK);

            ExitProcess(0);
        }
    }

    return reinterpret_cast<decltype(&DirectInputCreate_Impl)>(lpDirectInputCreate)(hinst, dwVersion, lplpDirectInput, punkOuter);
}