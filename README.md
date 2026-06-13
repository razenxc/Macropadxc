# 🕹️ [Macropadxc](https://github.com/razenxc/Macropadxc)

## Prototypes

| V1 | V2 | V3| V4 |
| :---: | :---: | :---: | :---: |
| <img width="200" alt="prototype 1" src="https://github.com/user-attachments/assets/6370f186-952d-4878-9d39-d4392d2f271d" /> | <img width="200" alt="prototype 2" src="https://github.com/user-attachments/assets/c967e57e-3924-4c00-a468-a79b0e5f346b" /> | <img width="200" alt="prototype 3" src="https://github.com/user-attachments/assets/decfb6ee-367b-40cd-8e0e-fe2dca8d4984" /> | <img width="200" alt="final prototype" src="https://github.com/user-attachments/assets/0fae24c2-e178-492b-94c9-b7aeecad5dcd" /> |

## Final prototype
| 1 | 2 |
| :---: | :---: |
| <img width="500" alt="20260530_221728" src="https://github.com/user-attachments/assets/d97d3ddc-9123-43c8-ad13-f4772b6c14ff" /> | <img width="500" alt="20260530_221754" src="https://github.com/user-attachments/assets/9d003f9a-2ed4-4905-b14f-01c454ca5fee" /> |



# 📖 [User Guide](README.md)

### 1. Getting Started

1. **Connect the Macropad:** Plug your Raspberry Pi Pico Macropad into an available USB port.
2. **Ensure the Service is Running:** The `MacropadxcService` background process must be active to intercept keystrokes. If you installed the app via the `.deb` or `.exe` installer, this service is configured to start automatically on login.
3. **Open the Client:** Launch the `Macropadxc` graphical client from your application menu or desktop shortcut to configure your keys.

### 2. Configuring Buttons

The graphical interface provides a grid that mirrors the 9 physical buttons on your hardware device. To assign a new function to a button:

1. Locate the target button in the list (e.g., **Button F1**).
2. Click the dropdown menu to select an **Action Type**.
3. If your selected action requires extra information (like a web address or a file path), a text input field will appear below it. Enter your target **Payload** there.

### 3. Available Actions & Payloads

You can assign the following types of commands to any key using the configuration file or GUI client:

* **Media Controls:** `Play/Pause`, `Previous`, `Next`.
* **Volume Controls:** `Volume Up`, `Volume Down`, `Mute`.
* **Open Website (URI):** Opens a specific URL in your default web browser.
  * *Payload Example:* `https://example.com`
* **Run Application:** Executes a system program, script, or opens a specific file.
  * *Payload Example (Windows):* `notepad.exe` or `C:\Tools\script.bat`
  * *Payload Example (Linux):* `gnome-calculator` or `/opt/scripts/run.sh`
* **None:** Disables the key completely.

#### ⌨️ Press Keys (Combo)
Simulates a complex keyboard shortcut at the OS level. Combine keys using the `+` symbol. This is fully cross-platform and works in games, OBS, and IDEs.
* *Payload Example:* `CTRL+SHIFT+ESC` or `WIN+D`

**Supported Keys (Case-insensitive):**

* **Alphanumeric:** Letters `A-Z` and numbers `0-9`
* **Modifiers:** * `CTRL` (or `CONTROL`), `LCTRL`, `RCTRL`
  * `SHIFT`, `LSHIFT`, `RSHIFT`
  * `ALT`, `LALT`, `RALT`
  * `WIN` (or `SUPER`, `META`), `RWIN`
* **Virtual Function Keys:** `F1` through `F24`
* **System & Special:** * `ESC` (or `ESCAPE`), `ENTER` (or `RETURN`), `TAB`, `SPACE`, `BACKSPACE`
  * `CAPSLOCK`, `APPS` (Menu Key), `PRINTSCREEN` (or `PRTSC`), `SCROLLLOCK`, `PAUSE`
* **Navigation:** * `UP`, `DOWN`, `LEFT`, `RIGHT`
  * `INSERT`, `DELETE` (or `DEL`), `HOME`, `END`, `PAGEUP`, `PAGEDOWN`
* **Numpad (Digital Block):** * `NUM0` to `NUM9`
  * `NUMMULTIPLY` (`*`), `NUMADD` (`+`), `NUMSUBTRACT` (`-`), `NUMDECIMAL` (`.`), `NUMDIVIDE` (`/`), `NUMLOCK`
* **Punctuation & Symbols:** * `;`, `:`, `+`, `=`, `,`, `<`, `-`, `_`, `.`, `>`, `/`, `?`, `~`, `[`, `{`, `]`, `}`, `\`, `|`, `'`, `"`
  * For the backtick key use: `` ` ``
* **Media Keys (Simulated Keystrokes):**
  * `VOLUP`, `VOLDOWN`, `MUTE`
  * `PLAYPAUSE`, `NEXTTRACK`, `PREVTRACK`

### 4. Applying Changes

The software features **Hot-Reloading**. The moment you change an action type or type a new payload in the GUI, the `config.json` file is automatically updated. The background service detects this change and applies your new settings instantly - no manual saving or restarting required!

# [💻 CLIENT](Client)
<img width="600" height="300" alt="image" src="https://github.com/user-attachments/assets/404570cb-1ead-4bd3-a36a-351355550535" />
<img width="600" alt="image" src="https://github.com/user-attachments/assets/40b3bae3-9f98-4fa8-9013-81bdf49a0373" />

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

Raspberry Pi Pico (YD-RP2040); 9 push buttons connected to individual pins; 3D printed case.

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






