libevdev-based, extensible driver for Asus NumPad written in C++20.

Now there are only classes for backlight control and backlight params interface with implementation for
- UP5401EA

## Building
Install dependencies:
- cmake (compile-time dependency)
- pkg-config (compile-time dependency)
- libevdev-devel (compile-time dependency)
- libevdev

Run these commands:
```shell
cmake -B build
cmake --build build
```
If you know exactly the model/layout of your numpad, you can specify it via CMake variable. For example:
```shell
cmake -B build -DINCLUDE_UP5401EA=ON
```