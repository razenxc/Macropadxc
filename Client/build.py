import shutil
import subprocess
import platform
from pathlib import Path

root = Path.cwd()
build_dir = root / "build"

if build_dir.exists():
    shutil.rmtree(build_dir) 
build_dir.mkdir()

if platform.system() == "Windows":
    shutil.copyfile(root/"dlls/msys-2.0.dll", build_dir/"msys-2.0.dll")

subprocess.run([
    "cmake",
    "-S", str(root),
    "-B", str(build_dir)
], check=True)

subprocess.run([
    "cmake",
    "--build", str(build_dir),
    "--config", "Release"
], check=True)