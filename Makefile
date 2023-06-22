.PHONY: default all lib-build lib-configure clean

default: all

all: lib-build

lib-build: lib-configure
	cmake --build build

lib-configure:
	cmake -B build \
		-G "Ninja Multi-Config" \
		-D CMAKE_EXPORT_COMPILE_COMMANDS=true \
		-D CMAKE_C_COMPILER=/bin/clang

clean:
	rm -rf build
