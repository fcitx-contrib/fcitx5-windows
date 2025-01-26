#include "../tsf/tsf.h"
#include "register.h"

CRITICAL_SECTION CS;
LONG dllRefCount = 0;

void DllAddRef() { InterlockedIncrement(&dllRefCount); }

void DllRelease() { InterlockedDecrement(&dllRefCount); }

class ClassFactory : public IClassFactory {
  public:
    // IUnknown methods
    STDMETHODIMP QueryInterface(REFIID riid, void **ppvObject) override {
        if (IsEqualIID(riid, IID_IClassFactory) ||
            IsEqualIID(riid, IID_IUnknown)) {
            *ppvObject = this;
            DllAddRef();
            return NOERROR;
        }
        *ppvObject = nullptr;
        return E_NOINTERFACE;
    }

    STDMETHODIMP_(ULONG) AddRef() override {
        DllAddRef();
        return dllRefCount;
    }

    STDMETHODIMP_(ULONG) Release() override {
        DllRelease();
        return dllRefCount;
    }

    // IClassFactory methods
    STDMETHODIMP CreateInstance(IUnknown *pUnkOuter, REFIID riid,
                                void **ppvObject) override {
        fcitx::Tsf *tsf;
        HRESULT hr;
        if (ppvObject == nullptr)
            return E_INVALIDARG;
        *ppvObject = nullptr;
        if (pUnkOuter != nullptr)
            return CLASS_E_NOAGGREGATION;
        if ((tsf = new fcitx::Tsf()) == nullptr)
            return E_OUTOFMEMORY;
        hr = tsf->QueryInterface(riid, ppvObject);
        tsf->Release(); // caller still holds ref if hr == S_OK
        return hr;
    }

    STDMETHODIMP LockServer(BOOL fLock) override {
        fLock ? DllAddRef() : DllRelease();
        return S_OK;
    }
};

ClassFactory *factory = nullptr;

__declspec(dllexport) STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid,
                                               void **ppvObject) {
    if (factory == nullptr) {
        EnterCriticalSection(&CS);
        if (factory == nullptr) {
            factory = new ClassFactory();
        }
        LeaveCriticalSection(&CS);
    }
    if (IsEqualIID(riid, IID_IClassFactory) || IsEqualIID(riid, IID_IUnknown)) {
        *ppvObject = factory;
        DllAddRef();
        return NOERROR;
    }
    *ppvObject = nullptr;
    return CLASS_E_CLASSNOTAVAILABLE;
}

__declspec(dllexport) STDAPI DllCanUnloadNow() { return dllRefCount == 0; }

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
