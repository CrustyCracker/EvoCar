#!/bin/bash -li
rm -rf build
mkdir build
g++ -std=c++17 src/main.cc src/imgui/*.cpp -o build/main -I include -L lib/linux -l sfml-system -l sfml-window -l sfml-graphics -l sfml-audio -l sfml-network -l box2d -l GL -Wl,-rpath ./lib/linu