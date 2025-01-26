#ifndef ASUS_NUMPAD_BACKLIGHT_CONSTRAINTS_HPP
#define ASUS_NUMPAD_BACKLIGHT_CONSTRAINTS_HPP
#include "params/abstract_params.hpp"

#include <array>
#include <cstdint>

namespace asus_numpad::backlight::details {
template <typename ParamsType>
concept ValidParams =
    requires(ParamsType params,
             std::array<uint8_t, ParamsType::BufSize()>& buf) {
      { params.FillBuf(buf) } -> std::same_as<void>;
    } &&
    (std::is_base_of_v<params::NonLevelAbstractParams<
                           ParamsType::BufSize(), ParamsType::Address(),
                           ParamsType::PowPos(), ParamsType::UsedI2C()>,
                       ParamsType> ||
     (std::is_base_of_v<params::LevelAbstractParams<
                            ParamsType::BufSize(), ParamsType::Address(),
                            ParamsType::PowPos(), ParamsType::LevelPos(),
                            ParamsType::UsedI2C()>,
                        ParamsType> &&
      requires(ParamsType params, uint8_t level) {
        { params.IsBacklightLevel(level) } -> std::same_as<bool>;
        { params.DefaultLevel() } -> std::same_as<uint8_t>;
      }));
}  // namespace asus_numpad::backlight::detail
#endif
