#include "tsf.h"

namespace fcitx {
bool Tsf::initKeyEventSink() {
    CComPtr<ITfKeystrokeMgr> keystrokeMgr;
    if (threadMgr_->QueryInterface(&keystrokeMgr) != S_OK) {
        return false;
    }
    return keystrokeMgr->AdviseKeyEventSink(clientId_, (ITfKeyEventSink *)this,
                                            TRUE) == S_OK;
}

void Tsf::uninitKeyEventSink() {
    CComPtr<ITfKeystrokeMgr> keystrokeMgr;
    if (threadMgr_->QueryInterface(&keystrokeMgr) != S_OK) {
        return;
    }
    keystrokeMgr->UnadviseKeyEventSink(clientId_);
}

BOOL Tsf::processKey(WPARAM wParam, LPARAM lParam) {
    HRESULT phrSession;
    textEditSinkContext_->RequestEditSession(
        clientId_, this, TF_ES_ASYNCDONTCARE | TF_ES_READWRITE, &phrSession);
    return TRUE;
}

STDMETHODIMP Tsf::OnSetFocus(BOOL fForeground) { return S_OK; }

STDMETHODIMP Tsf::OnTestKeyDown(ITfContext *pContext, WPARAM wParam,
                                LPARAM lParam, BOOL *pfEaten) {
    if (keyDownHandled_) {
        *pfEaten = TRUE;
    } else {
        *pfEaten = keyDownHandled_ = processKey(wParam, lParam);
    }
    return S_OK;
}

STDMETHODIMP Tsf::OnKeyDown(ITfContext *pContext, WPARAM wParam, LPARAM lParam,
                            BOOL *pfEaten) {
    if (keyDownHandled_) {
        keyDownHandled_ = FALSE;
        *pfEaten = TRUE;
    } else {
        *pfEaten = keyDownHandled_ = processKey(wParam, lParam);
    }
    return S_OK;
}

STDMETHODIMP Tsf::OnTestKeyUp(ITfContext *pContext, WPARAM wParam,
                              LPARAM lParam, BOOL *pfEaten) {
    return S_OK;
}

STDMETHODIMP Tsf::OnKeyUp(ITfContext *pContext, WPARAM wParam, LPARAM lParam,
                          BOOL *pfEaten) {
    return S_OK;
}

STDMETHODIMP Tsf::OnPreservedKey(ITfContext *pContext, REFGUID rguid,
                                 BOOL *pfEaten) {
    return S_OK;
}
} // namespace fcitx
