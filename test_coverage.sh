cd build/
ctest --progress
lcov -c -d . -o code_coverage.info
lcov --remove code_coverage.info '/usr/*' --output-file code_coverage.info
lcov --remove code_coverage.info /*/sfml-src/* --output-file code_coverage.info
lcov --remove code_coverage.info /*/imgui-src --output-file code_coverage.info
lcov --remove code_coverage.info /*/googletest-src/* --output-file code_coverage.info
lcov --remove code_coverage.info /*/_deps/* --output-file code_coverage.info
lcov --remove code_coverage.info /*/test/* --output-file code_coverage.info
genhtml code_coverage.info --output-directory ../CodeCoverageReport