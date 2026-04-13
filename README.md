# [💻 CLIENT](Client)

## 🐧 Linux

**Tested on:** Debian 13 (Trixie) + KDE Plasma + Wayland

### 📦 Runtime Requirements
> [!NOTE]  
> If you install via the `.deb` package, these dependencies will be installed automatically. Otherwise, you must install them manually.

- `playerctl` (for media keys)
- `pulseaudio-utils` (for volume control)
- `xdg-utils` (for opening URLs/files)
- `ydotool` (for keystroke simulation)

> [!IMPORTANT]  
> **For Debian 13 (Trixie) users:** `ydotool` is temporarily located in the backports repository. Enable it before installation:
> `echo "deb http://deb.debian.org/debian trixie-backports main" | sudo tee /etc/apt/sources.list.d/backports.list`

### ⚙️ Post-Installation Steps
> [!WARNING]  
> 1. You **MUST** add your user to the `input` group to allow `ydotool` to simulate keystrokes:
>    `sudo usermod -aG input $USER`
> 2. You must **log out and log back in** (or reboot) for the group permissions to apply and for the `macropadxc.service` auto-start to take effect.

### 🛠️ Build from Source
**1. Install Build Dependencies:**
- CMake, C++ Compiler, Python 3
- `sudo apt install libwayland-dev libxkbcommon-dev xorg-dev`
*(More details: [GLFW Compile Guide](https://www.glfw.org/docs/latest/compile_guide.html#compile_deps_wayland))*

**2. Compile Project:**
```bash
python3 build.py
````

**3. Build `.deb` Installer (Requires [dpkg](https://wiki.debian.org/dpkg)):**

```bash
cd build
cpack -G DEB
```

-----

## 🪟 Windows

### 📦 Runtime Requirements

  - Microsoft Visual C++ Redistributable

### 🛠️ Build from Source

**1. Install Build Dependencies:**

  - CMake, MSVC (Visual Studio Build Tools), Python 3

**2. Compile Project:**

```cmd
py build.py
```

**3. Build `.exe` Installer (Requires [NSIS](https://nsis.sourceforge.io/Download)):**

```cmd
cd build
cpack -G NSIS
```

-----

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

-----

-----

-----

# [🎛️ FIRMWARE](https://www.google.com/search?q=Firmware)

## 🧰 Dependencies

  - PlatformIO

### 📟 Hardware:

Raspberry Pi Pico (YD-RP2040); 9 push buttons connected to individual ports; 3D printed case.

## 🔌 Pinout

```text
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

### ⚡ Baud speed 115200

### 📲 Protocol Describing

#### 1\. Button pressed

`F<button number>`

  - Example Data:
      - TX `F1`
      - TX `F4`
      - TX `F8`

#### 2\. Port auto-detection

  - RX: `WAREI_HEY`
  - TX: `WAREI_OK`