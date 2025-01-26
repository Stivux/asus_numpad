#ifndef ASUS_NUMPAD_BACKLIGHT_HPP
#define ASUS_NUMPAD_BACKLIGHT_HPP
#include "common_backlight.hpp"
#include "level_backlight.hpp"

namespace asus_numpad::backlight {
namespace details {
template <typename ParamsType>
struct BackLightHelper : ParamsType {
  static constexpr bool has_level = ParamsType::HasBacklightLevel();
};
}  // namespace details

template <typename ParamsType>
using BackLight =
    std::conditional_t<details::BackLightHelper<ParamsType>::has_level,
                       details::LevelBackLight<ParamsType>,
                       details::CommonBackLight<ParamsType>>;
}  // namespace asus_numpad::backlight
#endif