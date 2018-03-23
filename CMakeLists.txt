cmake_minimum_required (VERSION 3.8)
project (Uberwald C)

set (UBW_VERSION_MAJOR 0)
set (UBW_VERSION_MINOR 0)
set (UBW_VERSION_PATCH 0)

set(CMAKE_PREFIX_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake ${CMAKE_PREFIX_PATH})

set (UBW_LIB_SOURCE_DIR ${PROJECT_SOURCE_DIR}/src)
set (UBW_CLI_SOURCE_DIR ${PROJECT_SOURCE_DIR}/src/cli)
set (UBW_TESTS_SOURCE_DIR ${PROJECT_SOURCE_DIR}/tests)

include_directories(${UBW_LIB_SOURCE_DIR})
include_directories(${UBW_CLI_SOURCE_DIR})

set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -std=c11 -pedantic")
set (CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS} -DDEBUG")
add_definitions(-DUBW_INTERNALS)

include_directories (
	"${PROJECT_SOURCE_DIR}"
	"${PROJECT_BINARY_DIR}" )

# * Intermediate products

# ** config.h

configure_file (
	"${PROJECT_SOURCE_DIR}/src/config.h.in"
	"${PROJECT_BINARY_DIR}/config.h")

# ** Ugly pseudo-metaprogramming pre-build script #

set (UBW_CONTAINERS_SRC ${PROJECT_BINARY_DIR}/containers.decl.h
  ${PROJECT_BINARY_DIR}/containers.impl.h)

add_custom_command(
  OUTPUT ${UBW_CONTAINERS_SRC}
  COMMAND ${UBW_LIB_SOURCE_DIR}/mkcontainers.sh ${UBW_LIB_SOURCE_DIR} ${PROJECT_BINARY_DIR}
  COMMENT "Generating containers source code..."
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
  DEPENDS ${UBW_LIB_SOURCE_DIR}/mkcontainers.sh
  ${UBW_LIB_SOURCE_DIR}/tpl/stack.tpl.h
  ${UBW_LIB_SOURCE_DIR}/tpl/stack.tpl.c
  ${UBW_LIB_SOURCE_DIR}/tpl/vector.tpl.h
  ${UBW_LIB_SOURCE_DIR}/tpl/vector.tpl.c
  ${UBW_LIB_SOURCE_DIR}/tpl/queue.tpl.h
  ${UBW_LIB_SOURCE_DIR}/tpl/queue.tpl.c)

# * Targets

# ** Library

set (UBW_LIB_SOURCES
  ${UBW_LIB_SOURCE_DIR}/containers.c
  ${UBW_LIB_SOURCE_DIR}/eval.c
  ${UBW_LIB_SOURCE_DIR}/object.c
  ${UBW_LIB_SOURCE_DIR}/print.c
  ${UBW_LIB_SOURCE_DIR}/read.c
  ${UBW_LIB_SOURCE_DIR}/store.c)

set (UBW_LIB_HEADERS
  ${UBW_LIB_SOURCE_DIR}/common.h
  ${UBW_LIB_SOURCE_DIR}/containers.h
  ${UBW_LIB_SOURCE_DIR}/env.h
  ${UBW_LIB_SOURCE_DIR}/eval.h
  ${UBW_LIB_SOURCE_DIR}/object.h
  ${UBW_LIB_SOURCE_DIR}/print.h
  ${UBW_LIB_SOURCE_DIR}/read.h
  ${UBW_LIB_SOURCE_DIR}/store.h
  ${UBW_LIB_SOURCE_DIR}/symbol.h
  ${UBW_LIB_SOURCE_DIR}/uberwald.h
  ${UBW_CONTAINERS_SRC})

add_library(LibUberwald SHARED
  ${UBW_LIB_SOURCES}
  ${UBW_LIB_HEADERS}
)

set_target_properties(LibUberwald PROPERTIES OUTPUT_NAME "uberwald")

# ** Tests

find_package(Check REQUIRED)

enable_testing()
include_directories(${CHECK_INCLUDE_DIRS})
add_executable(TestSuite
  ${UBW_TESTS_SOURCE_DIR}/main.c
  ${UBW_TESTS_SOURCE_DIR}/stack_test.c
  ${UBW_TESTS_SOURCE_DIR}/object_test.c
  ${UBW_TESTS_SOURCE_DIR}/read_test.c)

target_link_libraries(TestSuite LibUberwald)
target_link_libraries(TestSuite ${CHECK_LIBRARIES})

SET_TARGET_PROPERTIES(TestSuite PROPERTIES OUTPUT_NAME "ubwtests")

add_test(TestSuite ${CMAKE_CURRENT_BINARY_DIR}/ubwtests)

# ** Documentation

find_package(Doxygen REQUIRED)

set (DOXYGEN_PROJECT_NAME "Überwald")
set (DOXYGEN_PROJECT_NUMBER "${UBW_VERSION_MAJOR}.${UBW_VERSION_MINOR}.${UBW_VERSION_PATCH}")
set (DOXYGEN_OPTIMIZE_OUTPUT_FOR_C YES)
set (DOXYGEN_EXTRACT_PRIVATE YES)
set (DOXYGEN_INPUT src)
set (DOXYGEN_RECURSIVE YES)

# doxygen_add_docs(LibUberwald)

# ** CLI Executable

message(">>> ${CMAKE_MODULE_PATH} ${CMAKE_PREFIX_PATH}")

find_package(Readline REQUIRED)

add_executable(CLI
  ${UBW_CLI_SOURCE_DIR}/cli.c
  ${UBW_LIB_HEADERS})

SET_TARGET_PROPERTIES(CLI PROPERTIES OUTPUT_NAME "uberwald")
target_link_libraries(CLI LibUberwald)
target_link_libraries(CLI readline)
