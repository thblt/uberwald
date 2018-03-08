#pragma once

#define UBW_VERSION_MAJOR 0
#define UBW_VERSION_MINOR 0
#define UBW_VERSION_PATCH 0

#define DEFN_0(name, lisp_name) LispObject * name ()
#define DEFN_1(name, lisp_name, arg0) LispObject * name (LispObject * arg0)
#define DEFN_2(name, lisp_name, arg0, arg1) LispObject * name (LispObject * arg0, LispObject * arg1)
#define DEFN_3(name, lisp_name, arg0, arg1, arg2) LispObject * name (LispObject * arg0, LispObject * arg1, LispObject * arg2)
#define DEFN_4(name, lisp_name, arg0, arg1, arg2, arg3) LispObject * name (LispObject * arg0, LispObject * arg1, LispObject * arg2, LispObject * arg3)
#define DEFN_MANY(name, lisp_name) LispObject * name (LispObject * args)

#define UBW_INTEGER_TYPE long int
#define UBW_FLOAT_TYPE double
