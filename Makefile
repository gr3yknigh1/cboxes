.PHONY: default all build configure test clean

CMAKE_CONF_FLAGS :=
CMAKE_BUILD_FLAGS :=

default: all

all: build

debug: CMAKE_CONF_FLAGS += -D BUILD_TESTING=true
debug: CMAKE_BUILD_FLAGS += --config Debug
debug: all

release: CMAKE_BUILD_FLAGS += --config Release
release: all

build: configure
	cmake --build build $(CMAKE_BUILD_FLAGS)

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
