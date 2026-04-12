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

### 📟 Hardware: Raspberry Pi Pick (YD-RP2040); 9 push buttons connected to individual ports; 3D printed case;

## 🔌 Pinout

```
0  - GND 
F1 - 15
F2 - 14
F3 - 13
F4 - 12
F5 - 11
F6 - 10
F7 - 9
F8 - 8
F9 - 7
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
