#!/usr/bin/env bash

set -e
set -o pipefail

function print_header() {
    echo -e "\n***** ${1} *****"
}

print_header "RUN cppcheck"
if [ "${1}" == "--local" ]; then
	CPPCHECK="cppcheck"
else
	CPPCHECK="./linters/cppcheck/cppcheck"
fi
${CPPCHECK} project --enable=all --error-exitcode=1 -I project/coordinate_average/coord project/coordinate_average/coord_arrays project/coordinate_average/parallel project/coordinate_average/sequential project/coordinate_average/tests project/coordinate_average/utils --suppress=missingIncludeSystem # --check-config

print_header "RUN cpplint.py"
python2.7 ./linters/cpplint/cpplint.py --extensions=c,cpp project/coordinate_average/coord/* project/coordinate_average/coord_arrays/* project/coordinate_average/parallel/* project/coordinate_average/sequential/* project/coordinate_average/tests/* project/coordinate_average/utils/*

print_header "SUCCESS"