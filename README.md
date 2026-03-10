# [💻 CLIENT](Client)

## 🐧 The Linux configuration under which everything was developed and tested:

### Debian 13 + KDE Plasma + Wayland

## 🐧 Requirements for linux

- `sudo apt install playerctl pulseaudio-utils xdg-utils`

## 🪟 Requirements for windows

- Microsoft Visual C++ Redistributable

---

## 🧰 Dependencies

- CMake 
- C++ Compiler
- Python (for build script)

## 🐧 Dependencies for linux

- `sudo apt install libwayland-dev libxkbcommon-dev xorg-dev`
- - More details: https://www.glfw.org/docs/latest/compile_guide.html#compile_deps_wayland

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
  "F1": {
    "type": "CMD_MEDIA_NEXT",
    "payload": "",
  },
  "F2": {
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
0 - GND 
1 - F1 D13
2 - F2 D12
3 - F3 D14
4 - F4 D27
5 - F5 D26
6 - F6 D25
7 - F7 D33
8 - F8 D32 
```

### ⚡Baud speed 115200

### 📲 Protocol Describing

#### 1. Button pressed

`F<button number>`

- Example Data:
  
  - TX `F1`
  
  - TX `F4`
  
  - TX `F8`

#### 2. Port auto-detection

RX: `WAREI_HEY`

TX: `WAREI_OK`

---
