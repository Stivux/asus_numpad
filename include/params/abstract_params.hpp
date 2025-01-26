#ifndef ASUS_NUMPAD_ABSTRACT_PARAMS_HPP
#define ASUS_NUMPAD_ABSTRACT_PARAMS_HPP
#include <array>
#include <cstddef>
#include <cstdint>

namespace asus_numpad::params::abstract {
template <size_t BuffSize, uint16_t Addr, size_t PowerPos, bool UseI2C,
          bool HasLevel>
  requires(BuffSize > 0 && PowerPos < BuffSize)
class AbstractParams {
 public:
  ~AbstractParams() = default;

 protected:
  static consteval size_t BufSize() { return BuffSize; }

  static consteval uint16_t Address() { return Addr; }

  static consteval size_t PowPos() { return PowerPos; }

  static consteval bool UsedI2C() { return UseI2C; }

  static consteval bool HasBacklightLevel() { return HasLevel; }

  static void FillBufByRef(std::array<uint8_t, BufSize()>& buf,
                           const std::array<uint8_t, BuffSize>& ref) {
    std::copy(ref.begin(), ref.end(), buf.begin());
  }
};
}  // namespace asus_numpad::params::abstract

namespace asus_numpad::params {
template <size_t BuffSize, uint16_t Addr, size_t PowerPos, size_t LevelPosition,
          bool UseI2C>
  requires(LevelPosition < BuffSize)
class LevelAbstractParams
    : protected abstract::AbstractParams<BuffSize, Addr, PowerPos, UseI2C,
                                         true> {
 protected:
  static consteval size_t LevelPos() { return LevelPosition; }
};

template <size_t BuffSize, uint16_t Addr, size_t PowerPos, bool UseI2C>
class NonLevelAbstractParams
    : protected abstract::AbstractParams<BuffSize, Addr, PowerPos, UseI2C,
                                         false> {};
}  // namespace asus_numpad::params

#endif
