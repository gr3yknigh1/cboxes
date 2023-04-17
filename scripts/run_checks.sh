#!/bin/sh

echo "======================="
echo " Running in debug mode"
echo "======================="

echo "ASan: "
make -s clean asan debug || exit
echo "LSan: "
make -s clean lsan debug || exit
echo "MSan: "
make -s clean msan debug || exit
echo "UBSan: "
make -s clean ubsan debug || exit

