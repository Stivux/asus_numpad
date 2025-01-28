#ifndef ASUS_NUMPAD_KEY_VAL_HPP
#define ASUS_NUMPAD_KEY_VAL_HPP
#include <array>
#include <cstddef>

namespace asus_numpad::utils::key_val {
template <typename T>
struct Pair {
  std::string_view key;
  T value;
};

template <typename T, std::size_t N>
class KeyValStore {
 public:
  KeyValStore() = delete;

  constexpr explicit KeyValStore(const std::array<Pair<T>, N>& data)
      : data_{data} {}

  constexpr const T& operator[](const std::string& key) const {
    for (const auto& pair : data_) {
      if (pair.key == key) {
        return pair.value;
      }
    }
    throw std::runtime_error("Key not found");
  }

 private:
  const std::array<Pair<T>, N> data_;
};
}  // namespace asus_numpad::utils::key_val

#endif
