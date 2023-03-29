#!/bin/sh
clang++-14 -std=c++17 src/main.cpp -o main_clang++ -I include -L lib/linux -l sfml-system -l sfml-window -l sfml-graphics -l sfml-audio -l sfml-network -l box2d -Wl,-rpath ./lib/linux
g++-12 -std=c++17 src/main.cpp -o main_g++ -I include -L lib/linux -l sfml-system -l sfml-window -l sfml-graphics -l sfml-audio -l sfml-network -l box2d -Wl,-rpath ./lib/linux
