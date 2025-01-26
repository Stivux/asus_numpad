#ifndef ASUS_NUMPAD_LEVEL_BACKLIGHT_HPP
#define ASUS_NUMPAD_LEVEL_BACKLIGHT_HPP

#include "common_backlight.hpp"

namespace asus_numpad::backlight::details {
template <typename ParamsType>
class LevelBackLight : public CommonBackLight<ParamsType> {
  static_assert(ParamsType::HasBacklightLevel() &&
                "Param must have backlight level");

 public:
  LevelBackLight() = delete;

  explicit LevelBackLight(const char* path)
      : CommonBackLight<ParamsType>(path) {
#ifdef NUMPAD_MANUAL
    Base::backlight_ = ParamsType::DefaultLevel();
#else
    const int cur_backlight = GetBacklight();
    Base::backlight_ = ParamsType::IsBacklightLevel(cur_backlight)
                           ? cur_backlight
                           : ParamsType::DefaultLevel();
#endif
  }

  [[nodiscard]] int GetBacklight() const {
#ifdef NUMPAD_MANUAL
    return Base::backlight_;
#endif
    if constexpr (ParamsType::UsedI2C()) {
      // Now we can't get real status using I2C;
      return Base::backlight_;
    } else {
      static constinit std::array<uint8_t, ParamsType::BufSize()> buf{};
      ParamsType::FillBuf(buf);
      if (CommonBackLight<ParamsType>::ReadIOCTL(Base::fd_, buf) < 1) {
        return -1;
      }
      return buf[ParamsType::LevelPos()];
    }
  }

  [[nodiscard]] int SetBacklight(const uint8_t level) {
    if (!ParamsType::IsBacklightLevel(level)) {
      return -1;
    }
    if (CommonBackLight<ParamsType>::SendCommand(ParamsType::LevelPos(),
                                                 level) < 0) {
      return -1;
    }
    Base::backlight_ = level;
    return 0;
  }

 private:
  using Base = CommonBackLight<ParamsType>;
};

}  // namespace asus_numpad::backlight::details

#endif