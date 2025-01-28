#ifndef ASUS_NUMPAD_KEY_VAL_HPP
#define ASUS_NUMPAD_KEY_VAL_HPP
#include <array>
#include <cstddef>

namespace asus_numpad::utils::key_val {
template <typename KeyType, typename ValueType>
struct KeyValPair {
  KeyType key;
  ValueType value;
};

template <std::equality_comparable KeyType, typename ValueType, std::size_t N>
class KeyValStore {
 public:
  KeyValStore() = delete;

  constexpr explicit KeyValStore(const std::array<KeyValPair<KeyType, ValueType>, N>& data)
      : data_{data} {}

  constexpr const ValueType& operator[](const KeyType& key) const {
    for (const auto& pair : data_) {
      if (pair.key == key) {
        return pair.value;
      }
    }
    throw std::runtime_error("Key not found");
  }

 private:
  const std::array<KeyValPair<KeyType, ValueType>, N> data_;
};
}  // namespace asus_numpad::utils::key_val

#endif
