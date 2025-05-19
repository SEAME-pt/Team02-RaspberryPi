#!/bin/bash

set -e

# Build
mkdir -p build
cd build 
cmake .. -DCMAKE_BUILD_TYPE=Debug
make

# Run tests (don't fail script on test errors to still generate coverage)
set +e
./InstrumentClusterTests
set -e

# Generate coverage info
lcov --capture --directory . --output-file coverage.info

# Remove unwanted paths (standard libs, tests, autogen)
lcov --remove coverage.info '/usr/*' '*tests/*' '*_autogen/*' --output-file QT-coverage-filtered.info

# Generate HTML report
genhtml QT-coverage-filtered.info --output-directory coverage-html

# Open HTML report in default browser
echo "Coverage report generated in coverage-html directory."
xdg-open coverage-html/index.html || firefox coverage-html/index.html || google-chrome coverage-html/index.html
