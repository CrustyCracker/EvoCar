# ZPR 23L Projekt

Oprogramowanie przeprowadzające ewolucję sztucznych pojazdów w 2D. Chodzi o wyewoluowanie pojazdu, który dotrze jak najdalej w zadanym czasie. Coś podobnego dostępne jest [online](http://rednuht.org/genetic_cars_2/). Przydatna może być biblioteka do symulacji fizyki, np. Box2D. Przed rozpoczęciem realizacji projektu proszę zapoznać się z zawartością [strony](http://staff.elka.pw.edu.pl/~rbiedrzy/ZPR/index.html).

## Autorzy

Jakub Mateusz Marcowski

Mateusz Łukasz Krakowski


## TLDR
`sh install_packages.sh`

`mkdir build`

`cd build`

`cmake ..`

`make`

`./EvoRacer`

`./Test`

test coverage: `sh test_coverage.sh` (plik index.html w CodeCoverageReport)

## Możliwości programu
Przyciski:
- 'Q' - wyjście z programu
- 'P' - pauza
- 'N' - następna generacja
## Użyte paczki
najlepiej użyć skryptu `sh install_packages.sh` (z tego katalogu)

Aby zainstalować paczki użyj komendy `sudo apt-get install <package_name>`
Potrzebne będą:



- Box2d - `libbox2d-dev` (2.4.1-2ubuntu1)
- Gtest - `libgtest-dev` (1.8.0-6)
- cmake - `cmake` (3.22.1-1ubuntu1)
- build-essential - `build-essential` (12.8ubuntu1)ls
- ImGui - `libimgui-dev` 
- sfml - `libsfml-dev` 
- udev - `libudev-dev`
- freetype - `libfreetype-dev`
- xrandr `libxrandr-dev`
- x11 `libx11-dev`

## Jak zbudować projekt
wykonaj skrypt `sh fresh_build.sh` (z tego katalogu)
## Program
- Upwenij się że pobrałeś wszystkie paczki
- `mkdir build`
- `cd build`
- `cmake ..`
- `make`
-  Plik wykonawczy: `./EvoRacer`
-  Testy: `./Test`
## Test Coverage
Ostatni test coverage znajdue się w katalogu CodeCoverageReport, plik index.html
Aby stowrzyć raport z pokrycia testami należy:

- zaisntalować lcov `sudo apt-get install lcov`

- Użyć skryptu z tego katalogu `sh test_coverage.sh`

- Otworzyć plik `index.html` w przeglądarce internetowej, znajdujący się w katalogu CodeCoverageReport


## Funkcjonalności

Głównym celem naszego projektu jest stworzenie programu w którym będzie można obserwować ewolucje sztucznych samochodzików starających się pokonać jak najdłuższy dystans w określonym przez użytkownika czasie.



