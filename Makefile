.PHONY: default all build configure test clean

CMAKE_CONF_FLAGS :=
CMAKE_BUILD_FLAGS :=

default: all

all: build

debug: CMAKE_CONF_FLAGS += -DBUILD_TESTING=true
debug: CMAKE_CONF_FLAGS += -DCMAKE_BUILD_TYPE=Debug
debug: CMAKE_BUILD_FLAGS += --config Debug
debug: all

release: CMAKE_BUILD_FLAGS += --config Release
release: CMAKE_CONF_FLAGS += -DCMAKE_BUILD_TYPE=Release
release: all

build: configure
	cmake --build build $(CMAKE_BUILD_FLAGS) --verbose

configure:
	cmake -B build \
		-DCMAKE_EXPORT_COMPILE_COMMANDS=true \
		$(CMAKE_CONF_FLAGS)

test:
	cd build; ctest -VV

check:
	cmake --build build --target lint
	cmake --build build --target tidy

format:
	cmake --build build --target format

rebuild:
	$(MAKE) clean configure check build test

clean:
	rm -rf build
