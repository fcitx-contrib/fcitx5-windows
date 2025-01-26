#include "tsf.h"

namespace fcitx {
STDMETHODIMP Tsf::DoEditSession(TfEditCookie ec) {
    CComPtr<ITfInsertAtSelection> insertAtSelection;
    if (textEditSinkContext_->QueryInterface(
            IID_ITfInsertAtSelection, (LPVOID *)&insertAtSelection) != S_OK) {
        return E_FAIL;
    }
    CComPtr<ITfRange> range;
    if (insertAtSelection->InsertTextAtSelection(ec, TF_IAS_QUERYONLY, nullptr,
                                                 0, &range) != S_OK) {
        return E_FAIL;
    }
    CComPtr<ITfContextComposition> contextComposition;
    if (textEditSinkContext_->QueryInterface(
            IID_ITfContextComposition, (void **)&contextComposition) != S_OK) {
        return E_FAIL;
    }
    CComPtr<ITfComposition> composition;
    if (contextComposition->StartComposition(ec, range, this, &composition) !=
            S_OK ||
        composition == nullptr) {
        return E_FAIL;
    }

    range->SetText(ec, 0, L"哈", 1);

    composition->EndComposition(ec);

    return S_OK;
}
} // namespace fcitx
