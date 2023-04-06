del build /F /Q
mkdir build
xcopy /s lib\windows build\
g++ -std=c++17 src/main.cpp src/imgui/*.cpp -o build/main -I include -L lib/windows -l sfml-system -l sfml-window -l sfml-graphics -l sfml-audio -l sfml-network -l box2d -lopengl32
