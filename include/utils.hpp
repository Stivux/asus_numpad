#ifndef ASUS_NUMPAD_UTILS_HPP
#define ASUS_NUMPAD_UTILS_HPP
#include <cctype>
#include <cstddef>

namespace asus_numpad::utils {
constexpr bool is_valid_path(const char* path, const char* prefix) {
  if (path == nullptr || prefix == nullptr) {
    return false;
  }
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
}  // namespace asus_numpad::utils

#endif  //ASUS_NUMPAD_UTILS_HPP
