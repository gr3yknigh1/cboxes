#!/bin/sh

echo "======================="
echo " Running in debug mode"
echo "======================="

echo "==> ASan: "
make -s clean asan || exit
echo "==> LSan: "
make -s clean lsan || exit
echo "==> MSan: "
make -s clean msan || exit
echo "==> UBSan: "
make -s clean ubsan || exit

