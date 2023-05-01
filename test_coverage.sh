cd build/
ctest --progress
lcov -c -d /src/. -o code_coverage.info
genhtml code_coverage.info --output-directory ../CodeCoverageReport