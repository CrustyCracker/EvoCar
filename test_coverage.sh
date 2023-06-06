cd build/
ctest --progress
cd src/
lcov -c -d . -o code_coverage.info
genhtml code_coverage.info --output-directory ../../CodeCoverageReport