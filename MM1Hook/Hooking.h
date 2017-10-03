#pragma once

template <typename T, typename = std::enable_if<sizeof(T) == sizeof(std::uintptr_t) && std::is_pointer<T>::value || std::is_member_function_pointer<T>::value>::type>
T get_as(std::uintptr_t address)
{
    return reinterpret_cast<T&>(address);
}

template <typename T>
T* get_ptr(std::uintptr_t address)
{
    return get_as<T*>(address);
}

template <typename T>
T& get_ref(std::uintptr_t address)
{
    return *get_ptr<T>(address);
}

template <typename Function>
struct is_function_pointer
    : std::integral_constant<bool, std::is_pointer<Function>::value && std::is_function<typename std::remove_pointer<Function>::type>::value>
{ };

struct DetourHook
{
    void* _pFunc;
    void* _pDetour;

    DetourHook()
        : _pFunc(nullptr)
        , _pDetour(nullptr)
    { }

    bool Hook(void* pFunc, void* pDetour);
    bool UnHook();
};

template <typename Function, typename = std::enable_if<is_function_pointer<Function>::value || std::is_member_function_pointer<Function>::value>::type>
struct FunctionHook : DetourHook
{
    FunctionHook(std::uintptr_t address, Function detour)
    {
        Hook(reinterpret_cast<void*>(address), (void*&) detour);
    }

    ~FunctionHook()
    {
        UnHook();
    }

    operator Function()
    {
        return reinterpret_cast<Function>(_pFunc);
    }

    template <typename... Args>
    auto operator()(Args&&... args)
    {
        return static_cast<Function>(*this)(std::forward<Args>(args)...);
    }
};
