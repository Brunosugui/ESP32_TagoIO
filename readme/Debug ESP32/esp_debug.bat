call "%~dp0..\bin\openocd.exe" -s ..\..\share\openocd\scripts\ -f interface\ftdi\esp32_devkitj_v1.cfg -f board\esp32-wrover.cfg
PAUSE