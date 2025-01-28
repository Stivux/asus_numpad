#include<gtest/gtest.h>
#include "utils.hpp"

using namespace asus_numpad::utils;
TEST(IsValidPath, PassEmpty) {
  ASSERT_FALSE(is_valid_path("", "i2c-"));
  ASSERT_FALSE(is_valid_path("", ""));
}

TEST(IsValidPath, CheckValid) {
  ASSERT_TRUE(is_valid_path("i2c-0", "i2c-"));
  ASSERT_TRUE(is_valid_path("i2c-128", "i2c-"));
  ASSERT_TRUE(is_valid_path("hidraw0", "hidraw"));
  ASSERT_TRUE(is_valid_path("hidraw128", "hidraw"));
}

TEST(IsValidPath, CheckInvalid) {
  ASSERT_FALSE(is_valid_path("i2c0", "i2c-"));
  ASSERT_FALSE(is_valid_path("i2c-0/", "i2c-"));
  ASSERT_FALSE(is_valid_path("hidraw-0", "hidraw"));
  ASSERT_FALSE(is_valid_path("hidraw0/", "hidraw"));
  ASSERT_FALSE(is_valid_path("i2c-0", "hidraw"));
}

TEST(ModuleLoaded, CheckLoaded) {
  ASSERT_TRUE(module_loaded("vfat"));
  ASSERT_TRUE(module_loaded("fat"));
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}