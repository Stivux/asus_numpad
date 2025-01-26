#ifndef ASUS_NUMPAD_PARAMS_UP5401EA_HPP
#define ASUS_NUMPAD_PARAMS_UP5401EA_HPP
#include "abstract_up5401ea.hpp"

namespace asus_numpad::params {
class ParamsUP5401EA
    : protected details::AbstractParamsUP5401EA<5, 13, 3, 4, false> {
 protected:
  static void FillBuf(std::array<uint8_t, BufSize()>& buf) {
    static constinit std::array<uint8_t, BufSize()> tmp = {Address(), 112, 3, 0, 0};
    FillBufByRef(buf, tmp);
  }
};
}  // namespace asus_numpad::params

#endif
