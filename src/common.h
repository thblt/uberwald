#pragma once

#include <stdint.h>

#define UBW_VERSION_MAJOR 0
#define UBW_VERSION_MINOR 0
#define UBW_VERSION_PATCH 1

#define DEFN //

typedef long int ubw_int;
typedef double ubw_float;
typedef int_least32_t ubw_char;
typedef int ubw_bool;

#define UBW_MAX_SYMBOL_LENGTH 512

#ifdef _UBERWALD_INTERNALS
typedef ubw_bool bool;
#define true 1
#define false 0
#endif
