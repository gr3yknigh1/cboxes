cmake_minimum_required(VERSION 3.10)
project(cboxes C)


set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED true)


set(
    PROJECT_SOURCES
    ${PROJECT_SOURCE_DIR}/src/algorithm.c
    ${PROJECT_SOURCE_DIR}/src/dynamic_array.c
    ${PROJECT_SOURCE_DIR}/src/hash.c
    ${PROJECT_SOURCE_DIR}/src/hashmap.c
    ${PROJECT_SOURCE_DIR}/src/link_node.c
    ${PROJECT_SOURCE_DIR}/src/linked_list.c
    ${PROJECT_SOURCE_DIR}/src/memory.c
    ${PROJECT_SOURCE_DIR}/src/pair.c
    ${PROJECT_SOURCE_DIR}/src/shallow.c
    ${PROJECT_SOURCE_DIR}/src/string.c
    ${PROJECT_SOURCE_DIR}/src/type.c
)


set(
    PROJECT_HEADERS
    ${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}/algorithm.h
    ${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}/assert.h
    ${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}/dynamic_array.h
    ${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}/hash.h
    ${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}/hashmap.h
    ${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}/link_node.h
    ${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}/linked_list.h
    ${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}/memory.h
    ${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}/pair.h
    ${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}/shallow.h
    ${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}/status.h
    ${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}/string.h
    ${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}/type.h
    )

set(
    PROJECT_TEST_SOURCES
    ${PROJECT_SOURCE_DIR}/tests/test_darray.c
    )

add_library(${PROJECT_NAME} STATIC ${PROJECT_SOURCES})


if (CMAKE_BUILD_TYPE STREQUAL "")
    set(CMAKE_BUILD_TYPE "Debug")
endif()

message(STATUS "Build Type: ${CMAKE_BUILD_TYPE}")
message(STATUS "Compiler: ${CMAKE_C_COMPILER_ID}")

if(CMAKE_C_COMPILER_ID STREQUAL "MSVC")
    # TODO(gr3yknigh1): Test this up
    if (CMAKE_BUILD_TYPE STREQUAL "Debug")
        message(WARNING "Add debug flags")
        target_compile_options(${PROJECT_NAME} PUBLIC /W4)
    elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
        target_compile_options(${PROJECT_NAME} PUBLIC /W4)
    endif()
elseif(CMAKE_C_COMPILER_ID STREQUAL "GNU" OR CMAKE_C_COMPILER_ID STREQUAL "Clang")
    if (CMAKE_BUILD_TYPE STREQUAL "Debug")
        target_compile_options(${PROJECT_NAME} PUBLIC -Wall -Wextra -Wpedantic -Werror -O0 -g)
    elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
        target_compile_options(${PROJECT_NAME} PUBLIC -Wall -Wextra -Wpedantic -Werror -O3)
    elseif(CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo")
        target_compile_options(${PROJECT_NAME} PUBLIC -Wall -Wextra -Wpedantic -Werror -O3 -g)
    elseif(CMAKE_BUILD_TYPE STREQUAL "MinSizeRel")
        target_compile_options(${PROJECT_NAME} PUBLIC -Wall -Wextra -Wpedantic -Werror -Os)
    endif()
endif()

target_include_directories(
    ${PROJECT_NAME}
    PRIVATE ${PROJECT_SOURCE_DIR}/include
    )

find_program(CLANG_TIDY_EXEC clang-tidy)
if(CLANG_TIDY_EXEC)
    message(STATUS "Found clang-tidy")
    set(CMAKE_EXPORT_COMPILE_COMMANDS true)
    add_custom_target(
        tidy
        COMMAND ${CLANG_TIDY_EXEC}
            --config-file="${PROJECT_SOURCE_DIR}/.clang-tidy"
            -p "${PROJECT_BINARY_DIR}/compile_commands.json"
            ${PROJECT_SOURCES} ${PROJECT_HEADERS} ${PROJECT_TEST_SOURCES}
        )
else()
    message(WARNING "clang-tidy not found")
    add_custom_target(
        tidy
        COMMAND echo "clang-tidy not available" && false
        )
endif()


find_program(CLANG_FORMAT_EXEC clang-format)
if(CLANG_FORMAT_EXEC)
    message(STATUS "Found clang-format")
    add_custom_target(
        lint
        COMMAND ${CLANG_FORMAT_EXEC}
            --Werror
            --dry-run
            ${PROJECT_SOURCES} ${PROJECT_HEADERS} ${PROJECT_TEST_SOURCES}
        )

    add_custom_target(
        format
        COMMAND ${CLANG_FORMAT_EXEC}
            --Werror
            -i
            ${PROJECT_SOURCES} ${PROJECT_HEADERS} ${PROJECT_TEST_SOURCES}
        )
else()
    message(WARNING "clang-format not found")
    add_custom_target(
        lint
        COMMAND echo "clang-format not avaiable" && false
        )

    add_custom_target(
        format
        COMMAND echo "clang-format not avaiable" && false
        )
endif()


# NOTE(gr3yknigh1): Horray, more bikes! Custom test suite lib
include(CTest)
enable_testing()

if(BUILD_TESTING)
    foreach(TEST_SRC IN LISTS PROJECT_TEST_SOURCES)
        get_filename_component(TEST_NAME ${TEST_SRC} NAME_WE)
        add_executable(${TEST_NAME} ${TEST_SRC})
        target_link_libraries(${TEST_NAME} ${PROJECT_NAME})
        target_include_directories(
            ${TEST_NAME}
            PRIVATE ${PROJECT_SOURCE_DIR}/include
            )
        add_test(
            NAME ${TEST_NAME}
            COMMAND ${TEST_NAME}
            )
    endforeach(TEST_SRC)
endif()

add_executable(${PROJECT_NAME}-testing ${PROJECT_SOURCE_DIR}/testing/main.c)
target_link_libraries(${PROJECT_NAME}-testing ${PROJECT_NAME})
target_include_directories(${PROJECT_NAME}-testing PUBLIC ${PROJECT_SOURCE_DIR}/include)

