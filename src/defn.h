#pragma once

#define DEFN_0(name, lisp_name) LispObject * name ()
#define DEFN_1(name, lisp_name, arg0) LispObject * name (LispObject * arg0)
#define DEFN_2(name, lisp_name, arg0, arg1) LispObject * name (LispObject * arg0, LispObject * arg1)
#define DEFN_3(name, lisp_name, arg0, arg1, arg2) LispObject * name (LispObject * arg0, LispObject * arg1, , LispObject * arg2)
#define DEFN_MANY(name, lisp_name) LispObject * name (LispObject * args)
