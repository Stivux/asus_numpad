#include <cstdio>
#include <cstring>

#include "utils.hpp"

namespace asus_numpad::utils {
int module_loaded(const char* module_name) {
  constexpr auto mod_file = "/proc/modules";
  static constinit char buf[4096];
  static constinit char* buf_ptr = buf;
  static constinit size_t buf_size = sizeof(buf);
  FILE* file = fopen(mod_file, "r");
  if (file == nullptr) {
    return -1;
  }
  int rc = 0;
  while (getline(&buf_ptr, &buf_size, file) != -1) {
    if (std::strstr(buf, module_name) != nullptr &&
        std::strstr(buf, "Live") != nullptr) {
      rc = 1;
      break;
    }
  }
#ifndef NDEBUG
  if (fclose(file) != 0)
    perror("Failed to close /proc/modules");
#else
  fclose(file);
#endif
  return rc;
}
}  // namespace asus_numpad::utils