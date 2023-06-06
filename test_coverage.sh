cd build/
ctest --progress
lcov -c -d src/. -o code_coverage.info
lcov --remove code_coverage.info '/usr/*' --output-file code_coverage.info
lcov --remove code_coverage.info '*build/*' --output-file code_coverage.info
genhtml code_coverage.info --output-directory ../CodeCoverageReport