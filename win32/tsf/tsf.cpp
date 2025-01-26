#include "tsf.h"
#include <cassert>

extern void DllAddRef();
extern void DllRelease();

namespace fcitx {
Tsf::Tsf() { DllAddRef(); }

Tsf::~Tsf() { DllRelease(); }

// Windows also queries ITfDisplayAttributeCollectionProvider
// {3977526D-1A0A-435A-8D06-ECC9516B484F} which is internal and we simply
// ignore.
STDAPI Tsf::QueryInterface(REFIID riid, void **ppvObject) {
    if (ppvObject == nullptr) {
        return E_INVALIDARG;
    }
    *ppvObject = nullptr;

    if (IsEqualIID(riid, IID_IUnknown) ||
        IsEqualIID(riid, IID_ITfTextInputProcessor))
        *ppvObject = (ITfTextInputProcessor *)this;
    else if (IsEqualIID(riid, IID_ITfTextInputProcessorEx))
        *ppvObject = (ITfTextInputProcessorEx *)this;
    else if (IsEqualIID(riid, IID_ITfThreadMgrEventSink))
        *ppvObject = (ITfThreadMgrEventSink *)this;
    else if (IsEqualIID(riid, IID_ITfTextEditSink))
        *ppvObject = (ITfTextEditSink *)this;
    else if (IsEqualIID(riid, IID_ITfKeyEventSink))
        *ppvObject = (ITfKeyEventSink *)this;
    else if (IsEqualIID(riid, IID_ITfEditSession))
        *ppvObject = (ITfEditSession *)this;

    if (*ppvObject) {
        AddRef();
        return S_OK;
    }
    return E_NOINTERFACE;
}

STDAPI_(ULONG) Tsf::AddRef() { return ++refCount_; }

STDAPI_(ULONG) Tsf::Release() {
    LONG ret = --refCount_;
    assert(refCount_ >= 0);
    if (refCount_ == 0) {
        delete this;
    }
    return ret;
}
} // namespace fcitx
