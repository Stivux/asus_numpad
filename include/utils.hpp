#ifndef ASUS_NUMPAD_UTILS_HPP
#define ASUS_NUMPAD_UTILS_HPP
#include <cctype>
#include <cstddef>
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
}  // namespace asus_numpad::utils

#endif  //ASUS_NUMPAD_UTILS_HPP