#ifndef ASUS_NUMPAD_UTILS_HPP
#define ASUS_NUMPAD_UTILS_HPP
#include <cctype>
#include <cstddef>
#include <filesystem>
#include <string_view>

namespace asus_numpad::utils {
constexpr bool is_valid_path(const std::string_view path,
                             const std::string_view prefix) {
  size_t pos = 0;
  for (; prefix[pos] != '\0'; ++pos) {
    if (path[pos] != prefix[pos]) {
      return false;
    }
  }
  if (path[pos] == '\0') {
    return false;
  }
  for (; path[pos] != '\0'; ++pos) {
    if (!isdigit(path[pos])) {
      return false;
    }
  }
  return true;
}

int module_loaded(std::string_view module_name);

template <bool UseI2C>
std::filesystem::path backlight_control_file(const std::string_view sub_path) {
  using namespace std::filesystem;
  const path dev_path = "/dev";
  if constexpr (UseI2C) {
    const size_t i2c_block_start = sub_path.find("i2c-");
    if (i2c_block_start == std::string_view::npos) {
      return {};
    }
    const size_t i2c_block_end = sub_path.find_first_of('/', i2c_block_start);
    if (i2c_block_end == std::string_view::npos) {
      return {};
    }
    return dev_path /
           sub_path.substr(i2c_block_start, i2c_block_end - i2c_block_start);
  } else {
    const path sys_full_path =
        path("/sys") / sub_path.substr(1) / "device/hidraw";
    if (!exists(sys_full_path)) {
      return {};
    }
    for (const auto& dir_entry : directory_iterator(sys_full_path)) {
      if (!is_directory(dir_entry)) {
        continue;
      }
      const path& filename_path = dir_entry.path().filename();
      if (is_valid_path(filename_path.c_str(), "hidraw")) {
        return dev_path / filename_path;
      }
    }
    return {};
  }
}
}  // namespace asus_numpad::utils

#endif  //ASUS_NUMPAD_UTILS_HPP