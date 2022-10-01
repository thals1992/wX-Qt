#!/bin/bash

cd build2
cmake ..
cmake --build . --config Debug
cd ..
cp build2/wxqt .
