#ifndef ASUS_NUMPAD_COMMON_BACKLIGHT_HPP
#define ASUS_NUMPAD_COMMON_BACKLIGHT_HPP

#include "backlight_constraints.hpp"
#include "utils.hpp"

#include <cstdint>
#include <stdexcept>
#include <system_error>

#include <fcntl.h>
#include <linux/hidraw.h>
#include <linux/i2c-dev.h>
#include <linux/i2c.h>
#include <sys/ioctl.h>
#include <unistd.h>

namespace asus_numpad::backlight::details {
template <typename ParamsType>
class CommonBackLight : protected ParamsType {
  static_assert(ValidParams<ParamsType>);

 public:
  CommonBackLight() = delete;

  explicit CommonBackLight(const char* path)
      : fd_(open(path, O_RDWR | O_NONBLOCK)) {
    if (constexpr const char* prefix =
            ParamsType::UsedI2C() ? "/dev/i2c-" : "/dev/hidraw";
        !utils::is_valid_path(path, prefix)) {
      if (fd_ > 0 && close(fd_) < 0) {
#ifndef NDEBUG
        perror("Failed to close file");
#endif
      }
      throw std::invalid_argument("Path is incompatible with the param.");
    }

    if (fd_ < 0) {
      throw std::system_error(errno, std::system_category(),
                              "Failed to open brightness device");
    }
    enabled_ = Enabled();
  }

  ~CommonBackLight() {
    if (fd_ > 0 && close(fd_) < 0) {
#ifndef NDEBUG
      perror("Failed to close file");
#endif
    }
  }

  inline int Enable() { return ActivationAction(true); }

  inline int Disable() { return ActivationAction(false); }

  [[nodiscard]] bool Enabled() const {
#ifdef NUMPAD_MANUAL
    return enabled_;
#endif
    if constexpr (ParamsType::UsedI2C()) {
      // Now we can't get real status using I2C;
      return enabled_;
    } else {
      static constinit std::array<uint8_t, ParamsType::BufSize()> buf{};
      ParamsType::FillBuf(buf);
      if (ReadIOCTL(fd_, buf) < 0) {
        return false;
      }
      return buf[ParamsType::PowPos()];
    }
  }

 protected:
  int SendCommand(const size_t pos, const uint8_t cmd) {
    static constinit std::array<uint8_t, ParamsType::BufSize()> buf{};
    ParamsType::FillBuf(buf);
    if constexpr (ParamsType::HasBacklightLevel()) {
      PrepareBackLight(buf);
    }
    buf[ParamsType::PowPos()] = enabled_;
    buf[pos] = cmd;
    return WriteIOCTL(fd_, buf);
  }

  inline static int ReadIOCTL(const int fd,
                              std::array<uint8_t, ParamsType::BufSize()>& buf) {
    const int result = PerformIOCTL(fd, buf, true);
#ifndef NDEBUG
    if (result < 0) {
      perror("ioctl failed");
    }
    return result;
#else
    return result;
#endif
  }

  const int fd_;
  uint8_t backlight_{0};

 private:
  bool enabled_{false};

  void PrepareBackLight(std::array<uint8_t, ParamsType::BufSize()>& buf) {
    if constexpr (ParamsType::HasBacklightLevel()) {
      buf[ParamsType::LevelPos()] = ParamsType::IsBacklightLevel(backlight_)
                                        ? backlight_
                                        : ParamsType::DefaultLevel();
    }
  }

  static int PerformIOCTL(const int fd,
                          std::array<uint8_t, ParamsType::BufSize()>& buf,
                          const bool is_read) {
    if constexpr (ParamsType::UsedI2C()) {
      static i2c_msg msg{};
      msg = {
          .addr = ParamsType::Address(),
          .flags = is_read ? static_cast<uint16_t>(I2C_M_RD)
                           : static_cast<uint16_t>(0),
          .len = ParamsType::BufSize(),
          .buf = buf.data(),
      };
      static i2c_rdwr_ioctl_data ioctl_data{};
      ioctl_data = {.msgs = &msg, .nmsgs = 1};
      return ioctl(fd, I2C_RDWR, &ioctl_data);
    } else {
      return is_read
                 ? ioctl(fd, HIDIOCGFEATURE(ParamsType::BufSize()), buf.data())
                 : ioctl(fd, HIDIOCSFEATURE(ParamsType::BufSize()), buf.data());
    }
  }

  inline static int WriteIOCTL(
      const int fd, std::array<uint8_t, ParamsType::BufSize()>& buf) {
    const int result = PerformIOCTL(fd, buf, false);
#ifndef NDEBUG
    if (result < 0) {
      perror("ioctl failed");
    }
    return result;
#else
    return result;
#endif
  }

  inline int ActivationAction(bool action) {
    if (SendCommand(ParamsType::PowPos(), action) < 0) {
      return -1;
    }
    enabled_ = action;
    return 0;
  }
};
}  // namespace asus_numpad::backlight::detail

#endif
