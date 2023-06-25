cmake_minimum_required(VERSION 3.10)
project(cboxes C)


set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED true)


set(
    PROJECT_SOURCES
    ${PROJECT_SOURCE_DIR}/src/darray.c
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
    ${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}/assert.h
    ${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}/darray.h
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

target_include_directories(
    ${PROJECT_NAME}
    PRIVATE ${PROJECT_SOURCE_DIR}/include
    )


if (MSVC)
    target_compile_options(${PROJECT_NAME} PUBLIC /W4)
else()
    target_compile_options(${PROJECT_NAME} PUBLIC -Wall -Wextra -Wpedantic -Werror)
endif()


find_program(CLANG_TIDY_EXEC clang-tidy)
if(CLANG_TIDY_EXEC)
    message(STATUS "Found clang-tidy")
else()
    message(ERROR "clang-tidy not found")
endif()


find_program(CLANG_FORMAT_EXEC clang-format)
if(CLANG_FORMAT_EXEC)
    message(STATUS "Found clang-format")
else()
    message(ERROR "clang-format not found")
endif()


find_program(VALGRIND_EXEC valgrind)
if(VALGRIND_EXEC)
    message(STATUS "Found valgrind")
else()
    message(ERROR "Valgrind not found")
endif()

