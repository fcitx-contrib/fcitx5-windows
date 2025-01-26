#include "tsf.h"

namespace fcitx {
STDMETHODIMP Tsf::OnCompositionTerminated(TfEditCookie ecWrite,
                                          ITfComposition *pComposition) {
    return S_OK;
}
} // namespace fcitx
