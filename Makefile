.PHONY: default all build configure test clean

CMAKE_CONF_FLAGS :=

default: all

all: build

debug: CMAKE_CONF_FLAGS += -D BUILD_TESTING=true
debug: all

build: configure
	cmake --build build

configure:
	cmake -B build \
		-G "Unix Makefiles" \
		-D CMAKE_EXPORT_COMPILE_COMMANDS=true \
		-D CMAKE_C_COMPILER=/bin/clang \
		$(CMAKE_CONF_FLAGS)

test:
	cd build; ctest -VV

clean:
	rm -rf build
