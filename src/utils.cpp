#include "utils.hpp"
#include <cstdio>
#include <fstream>
#include <limits>

namespace asus_numpad::utils {
int module_loaded(const std::string_view module_name) {
  std::string buf;
  buf.reserve(4096);
  if (auto stream = std::ifstream("/proc/modules"); stream.is_open()) {
    for (stream >> buf; stream.good() && module_name != buf; stream >> buf) {
      stream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    if (stream.eof()) {
      return 0;
    }
    std::getline(stream, buf);
    return (buf.find("Live") != std::string::npos);
  }
  return -1;
}
}  // namespace asus_numpad::utils