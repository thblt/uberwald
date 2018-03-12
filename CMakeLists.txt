cmake_minimum_required (VERSION 3.8.2)
project (Uberwald C)

set (UBW_VERSION_MAJOR 0)
set (UBW_VERSION_MINOR 0)
set (UBW_VERSION_PATCH 0)

set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -std=c11 -pedantic")
add_definitions(-D_UBERWALD_INTERNALS)

set (PROJECT_SOURCE_DIR src)

configure_file (
	"${PROJECT_SOURCE_DIR}/config.h.in"
	"${PROJECT_BINARY_DIR}/config.h"
  )

include_directories (
	"${PROJECT_SOURCE_DIR}"
	"${PROJECT_BINARY_DIR}" )

####################
# Libraries        #
####################

find_library(Readline REQUIRED)
find_library(Check REQUIRED)

####################
# Targets          #
####################

# Library
# -------

add_library(LibUberwald SHARED ${PROJECT_SOURCE_DIR}/eval.c
  ${PROJECT_SOURCE_DIR}/object.c
  ${PROJECT_SOURCE_DIR}/read.c
  ${PROJECT_SOURCE_DIR}/stack.c
  ${PROJECT_SOURCE_DIR}/store.c)

set_target_properties(LibUberwald PROPERTIES OUTPUT_NAME "uberwald")

# CLI Executable
# --------------

add_executable(CLI ${PROJECT_SOURCE_DIR}/cli.c )

SET_TARGET_PROPERTIES(CLI PROPERTIES OUTPUT_NAME "uberwald")
target_link_libraries(CLI LibUberwald)
target_link_libraries(CLI readline)
