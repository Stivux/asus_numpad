#ifndef ASUS_NUMPAD_PARAMS_B7402_I2C_HPP
#define ASUS_NUMPAD_PARAMS_B7402_I2C_HPP

#include "params/abstract_params.hpp"

namespace asus_numpad::params {

class ParamsB7402_I2C : protected NonLevelAbstractParams<13, 0x15, 11, true> {
 protected:
  static void FillBuf(std::array<uint8_t, BufSize()>& buf) {
    static constinit std::array<uint8_t, BufSize()> tmp = {0x05, 0x00, 0x3d, 0x03, 0x06,
                                                 0x00, 0x07, 0x00, 0x0d, 0x14,
                                                 0x03, 0,    0xad};
    FillBufByRef(buf, tmp);
  }
};

}  // namespace asus_numpad::params

#endif