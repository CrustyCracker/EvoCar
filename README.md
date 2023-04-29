# ZPR 23L Projekt

Oprogramowanie przeprowadzające ewolucję sztucznych pojazdów w 2D. Chodzi o wyewoluowanie pojazdu, który dotrze jak najdalej w zadanym czasie. Coś podobnego dostępne jest [online](http://rednuht.org/genetic_cars_2/). Przydatna może być biblioteka do symulacji fizyki, np. Box2D. Przed rozpoczęciem realizacji projektu proszę zapoznać się z zawartością [strony](http://staff.elka.pw.edu.pl/~rbiedrzy/ZPR/index.html).

## Autorzy

Jakub Mateusz Marcowski
Mateusz Łukasz Krakowski

## Prowadzący projektu

rafal.biedrzycki@pw.edu.pl

## Przydatne linki

### Sprawka

- Sprawozdania https://www.overleaf.com/9151369263rntrszjsxfsx

### Projekt

- Strona projektu: http://staff.elka.pw.edu.pl/~rbiedrzy/ZPR/index.html
- Styl kodowania: http://staff.elka.pw.edu.pl/~rbiedrzy/ZPR/StylKodowania.html
- Porady: http://staff.elka.pw.edu.pl/~rbiedrzy/ZPR/porady.html

### Biblioteki

- box2d https://box2d.org/documentation/

## Użyte paczki

Aby zainstalować paczki użyj komendy `sudo apt-get install <package_name>`
Potrzebne będą:

- Box2d - `libbox2d-dev` (2.4.1-2ubuntu1)
- SFML - `libsfml-dev`  (2.5.1+dfsg-2)
- imgui - `libimgui-dev` (1.86+ds-1build1)
## Funkcjonalności

Głównym celem naszego projektu jest stworzenie programu w którym będzie można obserwować ewolucje sztucznych samochodzików starających się pokonać jak najdłuższy dystans w określonym przez użytkownika czasie.

## notatki do cmake

configurate and generate build files
`cmake ../zpr_23l_projekt/`

build
`cmake --build . --target`


JAKIES BLEDNY CMAKE 

CMake Error at cmake/Macros.cmake:296 (message):
  Missing item in X11_X11_LIB;X11_Xrandr_LIB
Call Stack (most recent call first):
  src/SFML/Window/CMakeLists.txt:239 (sfml_find_package)


fix
```sudo apt-get update
sudo apt-get install libx11-dev libxrandr-dev
```

CMake Error at _deps/sfml-src/cmake/Macros.cmake:296 (message):
  Missing item in FREETYPE_LIBRARY
Call Stack (most recent call first):
  _deps/sfml-src/src/SFML/Graphics/CMakeLists.txt:137 (sfml_find_package)

sudo apt-get install libfreetype-dev



DO BOX2d I TAK NIE DZIALA XDASX
sudo apt-get install xorg-dev