# 💻 CLIENT (aka User-Mode Driver)

## Requirements for linux: 
Tested on Debian 13 + KDE Plasma + Wayland
- `sudo apt install playerctl pulseaudio-utils xdg-utils`

---

## Dependencies: 
- CMake 
- C++ Compiler
- Python (for build script)

## Build:
  
  ```
  python3 build.py
  ```

## Third-Party:
- [wjwwood/serial](https://github.com/wjwwood/serial.git)

---
---
---

# 🎛️FIRMWARE

## Dependenices: 
- PlatformIO

### Hardware: Espressif ESP-32 and 8x2 push buttons connected to individual pins.

## Pinout

```
0 - gnd 
1 - f1 d13
2 - f2 d12
3 - f3 d14
4 - f4 d27
5 - f5 d26
6 - f6 d25
7 - f7 d33
8 - f8 d32 
```

## Protocol Describing

1. Button pressed
   `P<page number>F<button number>`
- Example Data:

- - `P0F1`

- - `P9F4`

- - `P3F8`

- Maximum 9 Pages (for simplification).
