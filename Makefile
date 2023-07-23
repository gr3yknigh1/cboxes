.PHONY: default all build configure test clean debug release run-sanitizers

CMAKE_CONF_FLAGS :=
CMAKE_BUILD_FLAGS :=

default: all

all: build

debug: CMAKE_CONF_FLAGS += -DBUILD_TESTING=true
debug: CMAKE_CONF_FLAGS += -DCMAKE_BUILD_TYPE=Debug
debug: CMAKE_BUILD_FLAGS += --config Debug
debug: configure

release: CMAKE_BUILD_FLAGS += --config Release
release: CMAKE_CONF_FLAGS += -DCMAKE_BUILD_TYPE=Release
release: configure

build: configure
	cmake --build build $(CMAKE_BUILD_FLAGS) --verbose

configure:
	cmake -B build \
		-DCMAKE_EXPORT_COMPILE_COMMANDS=true \
		$(CMAKE_CONF_FLAGS)

test:
	cmake --build build $(CMAKE_BUILD_FLAGS)
	cd build; ctest -VV

check:
	cmake --build build --target lint
	cmake --build build --target tidy

format:
	cmake --build build --target format

run-sanitizers:
	$(MAKE) clean
	cmake -B build \
		-DCMAKE_EXPORT_COMPILE_COMMANDS=true \
		-DSANITAZER=MSan \
		-DBUILD_TESTING=true \
		-DCMAKE_BUILD_TYPE=Debug

	cmake --build build --config Debug
	$(MAKE) test

	$(MAKE) clean
	cmake -B build \
		-DCMAKE_EXPORT_COMPILE_COMMANDS=true \
		-DSANITAZER=ASan \
		-DBUILD_TESTING=true \
		-DCMAKE_BUILD_TYPE=Debug
	cmake --build build --config Debug
	$(MAKE) test

	$(MAKE) clean
	cmake -B build \
		-DCMAKE_EXPORT_COMPILE_COMMANDS=true \
		-DSANITAZER=TSan \
		-DBUILD_TESTING=true \
		-DCMAKE_BUILD_TYPE=Debug
	cmake --build build --config Debug
	$(MAKE) test


clean:
	rm -rf build
