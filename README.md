# Projekt EvoCar 2023

## Autorzy

Jakub Mateusz Marcowski

Mateusz Łukasz Krakowski


## Zarys projektu
![[EvoCar](images\EvoCar.png)](https://github.com/CrustyCracker/EvoCar/blob/main/images/EvoCar.png)
Stworzyliśmy aplikację realizującą ewolucję sztucznych pojazdów. W tym celu skorzystaliśmy z algorytmu ewolucyjnego z selekcją turniejową i mutacją gaussowską. Samochód składa się z dwóch kół oraz szkieletu.

W skład genomu pojazdu wchodzi:
- rozmiar kół
- rozstawienie wierzchołków w szkielecie samochodu
- gęstość kół
- gęstość szkieletu samochodu

## Funkcjonalności

### Obserwacja zachodzącej mutacji samochodzików

Funkcjonalność w pełni zrealizowana, hiperparametry mutacji możemy zmienić w pliku `config/EvolutionaryAlgorithmConfig.cc`. Jeśli chcemy wymusić przejście do następnej generacji, możemy kliknąć przycisk "N".

### Generator samochodzików z możliwością zmiany parametrów samochodzika (prędkość zadana, maksymalna gęstość, minimalna gęstość)

Samochodziki generowane są na podstawie chromosomu jaki podamy do generatora samochodzików. Maksymalne i minimalne wartości atrybutów chromosomu możemy zmieniać w `config/EvolutionaryAlgorithmConfig.cc`, natomiast prędkość zadaną samochodzika można zmienić w `config/CarConfig.cc`.

### Generator mapy z możliwością zmiany parametrów (minimalna i maksymalna zmiana nachylenia terenu)

Mapa jest generowana losowo, hiperparametry generatora można zmieniać w pliku `config/EvolutionaryAlgorithmConfig.cc`.

### Mechanizm ewolucji samochodzików z możliwością zmiany jego parametrów

Do realizacji tej funkcjonalności wybraliśmy algorytm ewolucyjny z mutacją gaussowską i selekcją turniejową. Hiperparametry algorytmu takie jak maksymalne i minimalne wartości atrybutów chromosomu, parametry inicjalizacji i mutacji chromosomu, liczbę uczestników turnieju itd. możemy zmieniać w `config/EvolutionaryAlgorithmConfig.cc`.

### Zapisywanie genomu i wyników samochodzików

Funkcjonalność włączamy lub wyłączamy zmieniając stałą `SAVE_TO_FILE` w pliku `config/Config.cc`, możemy również zmienić ścieżkę pliku, w którym zapisywane mają być dane chromosomów.

### Dodatkowo: Wykresy

Dodatkowo postanowiliśmy wprowadzić do programu rysowanie wykresu prędkości i obecnej pozycji samochodzików.

## Instrukcja obsługi

### Instalacja
Postępuj zgodnie z tym, co zawarte w pliku README.md.

### Funkcje programu
Następujące klawisze odpowiadają za:
- "Q" - wyjdź z programu
- "N" - wymuś przejście do następnej generacji
- "P" - zatrzymaj symulację, ponowne kliknięcie wznawia symulację

## Architektura aplikacji

![[Diagram_klas](images\Diagram_klas.png)](https://github.com/CrustyCracker/EvoCar/blob/main/images/Diagram_klas.png)

### EvolutionaryAlgorithm
`EvolutionaryAlgorithm` to klasa odpowiedzialna za ewolucję chromosomów. Do populacji dostajemy się przez funkcję `getPopulation()`, gdy kończymy iterację symulacji to podajemy fitness każdego z chromosomów przez funkcję `setFitness()`, a następnie wykonujemy `nextStep()`.

### Shape
W pliku `Shape.h` zdefiniowane są struktury potrzebne do symulacji, takie jak Box, Circle i Polygon.

## Zadania

### Wykonane zadania

Po lewej planowany czas, po prawej czas faktycznie spędzony

1. Planowanie (10h -> 10h):
   - Wybór odpowiednich bibliotek  2h -> 2h
   - Rozpisanie zadań  6h -> 6h
   - Podział odpowiedzialności  2h -> 2h

2. Szkielet aplikacji (24h -> 36h):
   - Zapoznanie się z biblioteką 2DBox  8h -> 12h
   - Stworzenie dema aplikacji  16h -> 24h

3. Implementacja samochodzika (24h -> 36h):
   - Klasa samochodzika  12h -> 18h
     - Koło  4h -> 6h
     - Szkielet  4h -> 6h
   - Generator samochodzików na podstawie podanego genomu  4h -> 6h

4. Implementacja mapy (20h -> 28h):
   - Mapa  8h -> 12h
     - Podłoże  4h -> 4h
   - Generator mapy  8h -> 12h

5. Implementacja algorytmu ewolucyjnego (32h -> 31h):
   - Klasa przechowująca populację  8h -> 12h
   - Funkcja inicjalizująca populację  2h -> 3h
   - Funkcja oceniająca samochód  6h -> 8h
   - Mechanizm selekcji  8h -> 4h
   - Mechanizm mutacji (mutacja gaussowska)  8h -> 4h
   - Mechanizm eksportowania danych samochodzików do zewnętrznego pliku  8h -> 10h
   - Rysowanie wykresów  0h -> 16h

### Porównanie estymaty z czasem rzeczywiście spędzonym nad projektem

Według naszych pozytywnych estymacji, projekt powinien potrwać 118 godzin, po 59 godzin na członka zespołu. Faktycznie nad projektem spędziliśmy 167 godzin.


## Dokumentacja
### TLDR
`sh install_packages.sh`

`mkdir build`

`cd build`

`cmake ..`

`make`

`./EvoRacer`

`./Test`

test coverage: `sh test_coverage.sh` (plik index.html w CodeCoverageReport)

### Możliwości programu
Przyciski:
- 'Q' - wyjście z programu
- 'P' - pauza
- 'N' - następna generacja
### Użyte paczki
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
### Program
- Upwenij się że pobrałeś wszystkie paczki
- `mkdir build`
- `cd build`
- `cmake ..`
- `make`
-  Plik wykonawczy: `./EvoRacer`
-  Testy: `./Test`
### Test Coverage
Ostatni test coverage znajdue się w katalogu CodeCoverageReport, plik index.html
Aby stowrzyć raport z pokrycia testami należy:

- zaisntalować lcov `sudo apt-get install lcov`

- Użyć skryptu z tego katalogu `sh test_coverage.sh`

- Otworzyć plik `index.html` w przeglądarce internetowej, znajdujący się w katalogu CodeCoverageReport





