# [💻 CLIENT](Client)

## 🐧 Requirements for linux
Tested on Debian 13 + KDE Plasma + Wayland
- `sudo apt install playerctl pulseaudio-utils xdg-utils`

---

## 🧰 Dependencies
- CMake 
- C++ Compiler
- Python (for build script)

## 🛠️ Build
### 🐧 Linux
  ```py
  python3 build.py
  ```
### 🪟 Windows
  ```py
  py build.py
  ```

## ⚙️ Configuration example
```json
[
  "P0F1": {
    "type": "CMD_MEDIA_NEXT",
    "payload": "",
  },
  "P0F2": {
    "type": "CMD_OPEN_URL",
    "payload": "https://github.com/razenxc",
  }
]
```

## 📚 Third-Party
- [wjwwood/serial](https://github.com/wjwwood/serial.git)
- [nlohmann/json](https://github.com/nlohmann/json)
- [ocornut/imgui](https://github.com/ocornut/imgui)
- [GLAD 1](https://glad.dav1d.de)
- [glfw/glfw](https://github.com/glfw/glfw)
---
---
---

# [🎛️FIRMWARE](Firmware)

## 🧰 Dependenices
- PlatformIO

### 📟 Hardware: Espressif ESP-32 and 8x2 push buttons connected to individual pins.

## 🔌 Pinout

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

## 📲 Protocol Describing

1. Button pressed
   `P<page number>F<button number>`
- Example Data:

- - `P0F1`

- - `P9F4`

- - `P3F8`

- Maximum 9 Pages (for simplification).

