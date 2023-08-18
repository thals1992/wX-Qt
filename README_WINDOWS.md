[TOC]
# Windows 10 
* This may work on versions as early as Windows 7 provided you have 64bit OS

## Obtain MSYS2 "Software Distribution and Building Platform for Windows" (Windows 7 or newer - 64bit)
[https://www.msys2.org/](https://www.msys2.org/)
* Under **Installation** click on the button next to `Download the installer`. As of Dec 2021 the button links to:
https://github.com/msys2/msys2-installer/releases/download/2021-11-30/msys2-x86_64-20211130.exe
* After installation a terminal window should open, follow these steps
```bash
pacman -Syu
# close window
```
* Run `MSYS2 MSYS` from Start menu. Update the rest of the base packages with
```
pacman -Su
pacman -S --needed base-devel mingw-w64-x86_64-toolchain
# close window
```
* run `MSYS MinGW 64-bit` from Windows Start menu and install necessary **Qt6** software along with **git**.
```
pacman -S git
pacman -S mingw-w64-x86_64-qt6-base
pacman -S mingw-w64-x86_64-qt6-tools
pacman -S mingw-w64-x86_64-qt6-location
```
* Download **wxqt** and compile/run.
```bash
git clone https://gitlab.com/joshua.tee/wxqt
cd wxqt/resourceCreation
./createResourcesImage.py
./createResourcesRes.py
cd ..
./makeAll.py
# after the initial compile just use
./run.bash
```


## Additional Reference Links
* [MSYS2 Detailed install guide](https://www.msys2.org/wiki/MSYS2-installation/)
* [MSYS2 Introduction](https://www.msys2.org/wiki/MSYS2-introduction/)
* [MSYS2 Packages](https://packages.msys2.org/package/)

