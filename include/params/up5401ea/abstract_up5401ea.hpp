#ifndef ASUS_NUMPAD_ABSTRACT_PARAMS_UP5401EA_HPP
#define ASUS_NUMPAD_ABSTRACT_PARAMS_UP5401EA_HPP
#include "params/abstract_params.hpp"

namespace asus_numpad::params::details {
template <size_t BuffSize, uint16_t Addr, size_t PowerPos, size_t LevelPosition,
          bool UseI2C>
class AbstractParamsUP5401EA
    : protected LevelAbstractParams<BuffSize, Addr, PowerPos, LevelPosition,
                                    UseI2C> {
 protected:
  [[nodiscard]] static constexpr bool IsBacklightLevel(const uint8_t level) {
    return kMinLevel <= level && level <= kMaxLevel;
  }

  [[nodiscard]] static consteval uint8_t DefaultLevel() { return kMaxLevel; }

 private:
  static constexpr uint8_t kMaxLevel = UseI2C ? 0x48 : 0x58;
  static constexpr uint8_t kMinLevel = UseI2C ? 0x41 : 0x51;
};
}  // namespace asus_numpad::params::details
#endif  //ASUS_NUMPAD_ABSTRACT_PARAMS_UP5401EA_HPP
