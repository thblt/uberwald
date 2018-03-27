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
set (CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -DDEBUG")

include_directories (
	"${PROJECT_SOURCE_DIR}"
	"${PROJECT_BINARY_DIR}" )

# * Configuration

# ** Reader

set(UBW_READER_STACK_SIZE 256 CACHE STRING
  "The default stack length of the reader.  This is equivalent to the maximum list nesting level.")

# ** Lisp

set(UBW_LISP_TYPES_INT_TYPE "long int" CACHE string
  "C type of Lisp integers")

set(UBW_LISP_TYPES_FLOAT_TYPE "double" CACHE string
  "C type of Lisp floats")

set(UBW_LISP_TYPES_CHAR_TYPE "int_least32_t" CACHE string
  "C type of Lisp chars.")

set(UBW_LISP_MAX_SYMBOL_LENGTH 512 CACHE STRING
  "Maximum length, in characters, of a symbol.")

# ** Storage

set(UBW_HEAP_MAX_FRAGMENTATION 128 CACHE STRING
  "Size of the symbols table.  This is the maximum number of symbols that can be interned.")

set(UBW_SYMTBL_SIZE 1024 CACHE STRING
  "Size of the symbols table.  This is the maximum number of symbols that can be interned.")

set(UBW_SYMTBL_SYMBID_SIZE 64 CACHE STRING
  "Size of a symbol id.")

set (UBW_SYMTBL_HASH "FNV1" CACHE STRING
  "The symbol hash algorithm.")

set(UBW_EPH_STORE_SIZE 1024 CACHE STRING
  "Size of the reader's ephemeral store. ")

# * Intermediate products

# ** config.h

configure_file (
	"${PROJECT_SOURCE_DIR}/src/config.h.in"
	"${PROJECT_BINARY_DIR}/config.h")

# * Targets

# ** Library

set (UBW_LIB_SOURCES
  ${UBW_LIB_SOURCE_DIR}/eval.c
  ${UBW_LIB_SOURCE_DIR}/heap.c
  ${UBW_LIB_SOURCE_DIR}/object.c
  ${UBW_LIB_SOURCE_DIR}/print.c
  ${UBW_LIB_SOURCE_DIR}/read.c
  ${UBW_LIB_SOURCE_DIR}/stack.c
  ${UBW_LIB_SOURCE_DIR}/symtbl.c)

set (UBW_LIB_HEADERS
  ${UBW_LIB_SOURCE_DIR}/common.h
  ${UBW_LIB_SOURCE_DIR}/env.h
  ${UBW_LIB_SOURCE_DIR}/eval.h
  ${UBW_LIB_SOURCE_DIR}/heap.h
  ${UBW_LIB_SOURCE_DIR}/object.h
  ${UBW_LIB_SOURCE_DIR}/print.h
  ${UBW_LIB_SOURCE_DIR}/read.h
  ${UBW_LIB_SOURCE_DIR}/stack.h
  ${UBW_LIB_SOURCE_DIR}/symtbl.h
  ${UBW_LIB_SOURCE_DIR}/uberwald.h
  ${UBW_CONTAINERS_SRC})

add_library(dylib SHARED
  ${UBW_LIB_SOURCES}
  ${UBW_LIB_HEADERS})

target_compile_definitions(dylib PRIVATE -DUBW_EXPOSE_INTERNALS)

set_target_properties(dylib PROPERTIES OUTPUT_NAME "uberwald")

# ** Tests

find_package(Check REQUIRED)

enable_testing()
include_directories(${CHECK_INCLUDE_DIRS})
add_executable(tests
  ${UBW_TESTS_SOURCE_DIR}/main.c
  ${UBW_TESTS_SOURCE_DIR}/stack_test.c
  ${UBW_TESTS_SOURCE_DIR}/object_test.c
  ${UBW_TESTS_SOURCE_DIR}/read_test.c
  ${UBW_TESTS_SOURCE_DIR}/symtbl_test.c)

target_compile_definitions(tests PRIVATE -DUBW_EXPOSE_INTERNALS)

target_link_libraries(tests dylib)
target_link_libraries(tests ${CHECK_LIBRARIES})

add_test(tests ${CMAKE_CURRENT_BINARY_DIR}/ubwtests)

# ** Documentation

if(CMAKE_VERSION VERSION_GREATER_EQUAL 3.9)
  find_package(Doxygen REQUIRED)

  set (DOXYGEN_PROJECT_NAME "Überwald")
  set (DOXYGEN_PROJECT_NUMBER "${UBW_VERSION_MAJOR}.${UBW_VERSION_MINOR}.${UBW_VERSION_PATCH}")
  set (DOXYGEN_OPTIMIZE_OUTPUT_FOR_C YES)
  set (DOXYGEN_EXTRACT_PRIVATE YES)
  set (DOXYGEN_RECURSIVE YES)

  doxygen_add_docs(apidoc ${UBW_LIB_HEADERS} ${UBW_LIB_SOURCES})
else()
  message(WARNING "API documentation generation requires CMake >= 3.9.  Dropping this target.")
endif()

# ** CLI Executable

message(">>> ${CMAKE_MODULE_PATH} ${CMAKE_PREFIX_PATH}")

find_package(Readline REQUIRED)

add_executable(CLI
  ${UBW_CLI_SOURCE_DIR}/cli.c
  ${UBW_LIB_HEADERS})

SET_TARGET_PROPERTIES(CLI PROPERTIES OUTPUT_NAME "uberwald")
target_link_libraries(CLI dylib)
target_link_libraries(CLI readline)
