#include "register.h"

CRITICAL_SECTION CS;

__declspec(dllexport) STDAPI DllUnregisterServer() {
    fcitx::UnregisterCategoriesAndProfiles();
    fcitx::UnregisterServer();
    return S_OK;
}

__declspec(dllexport) STDAPI DllRegisterServer() {
    if (fcitx::RegisterServer() && fcitx::RegisterProfiles() &&
        fcitx::RegisterCategories()) {
        return S_OK;
    }
    DllUnregisterServer();
    return E_FAIL;
}

BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID pvReserved) {
    switch (dwReason) {
    case DLL_PROCESS_ATTACH:
        fcitx::dllInstance = hInstance;
        if (!InitializeCriticalSectionAndSpinCount(&CS, 0)) {
            return FALSE;
        }
        break;
    case DLL_PROCESS_DETACH:
        DeleteCriticalSection(&CS);
        break;
    }
    return TRUE;
}
