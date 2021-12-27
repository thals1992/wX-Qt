#!/bin/bash
#
# must be run in the project directory as build/ is removed
# removes prior build dir, runs qmake, and compiles
#
# use qmake6 or similar and do manual for qt6 build
#
rm -rf build

cd resourceCreation
./createResourcesImage.py
./createResourcesRes.py
cd ..
./makePro.py

if grep -q "Fedora Linux" /etc/os-release
then
    qmake-qt5
elif grep -q "MSYS2" /etc/os-release
then
    qmake6
else
    qmake
fi
./run.bash "$@"
