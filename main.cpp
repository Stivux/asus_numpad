#include <backlight/backlight.hpp>
#include <iostream>
#include "key_val.hpp"
#include "params/params.hpp"

// This is just an example of how it might work.
template <typename ParamsType>
class NumpadExample : asus_numpad::backlight::BackLight<ParamsType> {
 public:
  NumpadExample() : Base("/dev/hidraw0") {}

  int EnableBackLight() { return Base::Enable(); }

  int DisableBackLight() { return Base::Disable(); }

  int SetBacklight(const uint8_t level)
    requires(std::is_same_v<
             asus_numpad::backlight::BackLight<ParamsType>,
             asus_numpad::backlight::details::LevelBackLight<ParamsType>>)
  {
    return Base::SetBacklight(level);
  }

  static consteval bool HasLevel() { return Base::HasBacklightLevel(); }

 private:
  using Base = asus_numpad::backlight::BackLight<ParamsType>;
};

template <typename ParamsType>
int start_numpad() {
  NumpadExample<ParamsType> numpad;
  int return_value = numpad.EnableBackLight();
  if constexpr (NumpadExample<ParamsType>::HasLevel()) {
    return_value |= numpad.SetBacklight(0x51);
  }
  return return_value;
}

using FuncPair = asus_numpad::utils::key_val::Pair<int (*)()>;

static constexpr auto start_funcs =
    asus_numpad::utils::key_val::KeyValStore(std::array{
#ifdef INCLUDE_UP5401EA
        FuncPair{"up5401ea", start_numpad<asus_numpad::params::ParamsUP5401EA>},
#endif

#ifdef INCLUDE_B7402
        FuncPair{"b7402", start_numpad<asus_numpad::params::ParamsB7402_I2C>},
#endif
    });

int main() {
  return start_funcs["up5401ea"]();
}
