.. _api-core-object-reference:

******
Object
******

An :c:type:`ubw_obj` is a simple recursive tagged union representing
any possible Lisp object.  A Lisp object has exactly nine possibles types:

 1. A **list**, initialized with :c:func:`ubw_list_init`.
 2. A **vector**, initialized with :c:func:`ubw_vector_init`.
 3. An **integer**, initialized with :c:func:`ubw_int_init`.
 4. A **floating-point number**, initialized with :c:func:`ubw_float_init`.
 5. A **character**, initialized with :c:func:`ubw_char_init`.
 6. A **string**, initialized with :c:func:`ubw_string_init`.
 7. A **symbol**, initialized with :c:func:`ubw_symbol_init`.
 8. A **keyword**, initialized with :c:func:`ubw_keyword_init`.
 9. A **C function**, initialized with :c:func:`ubw_cfunc_init`.


Data structures
===============

.. warning:: Don't manipulate these data structures directly.
             Instead, see the various accessors this library
             provides.

.. doxygenstruct:: ubw_obj

.. doxygenstruct:: ubw_cfunc

Functions
=========

This library provides only very fundamental functions, falling mostly
under three categories:

 - **Constructors**, which initialize a memory slot as an object of a
   given type with a given value;
 - **Type predicates**, used to determine whether an object is of a
   given type;
 - **Unboxing functions**, which return the underlying value of an
   object.

Constructors
------------

.. doxygenfunction:: ubw_list_init
.. doxygenfunction:: ubw_vector_init
.. doxygenfunction:: ubw_int_init
.. doxygenfunction:: ubw_float_init
.. doxygenfunction:: ubw_char_init
.. doxygenfunction:: ubw_string_init
.. doxygenfunction:: ubw_symbol_init
.. doxygenfunction:: ubw_keyword_init
.. doxygenfunction:: ubw_cfunc_init

Type predicates
---------------

The boolean predicates simply return true if the function is of the
given type.  They're equivalent to the usual Lisp predicates, although
those are inline.

.. doxygenfunction:: ubw_list_p
.. doxygenfunction:: ubw_vector_p
.. doxygenfunction:: ubw_int_p
.. doxygenfunction:: ubw_float_p
.. doxygenfunction:: ubw_char_p
.. doxygenfunction:: ubw_string_p
.. doxygenfunction:: ubw_symbol_p
.. doxygenfunction:: ubw_keyword_p
.. doxygenfunction:: ubw_cfunc_p

Unboxing
--------

The various `ubw_*_unbox` functions simply return the underlying value
of the object they receive.  If assertions are enabled, they abort if
the object they receive is not of the type they're supposed to unbox.

Notice that since lists hold *two* values, there's no
``ubw_list_unbox``.  Instead, see :c:func:`ubw_list_car` and :c:func:`ubw_list_cdr`.

.. doxygenfunction:: ubw_list_car
.. doxygenfunction:: ubw_vector_unbox
.. doxygenfunction:: ubw_int_unbox
.. doxygenfunction:: ubw_float_unbox
.. doxygenfunction:: ubw_char_unbox
.. doxygenfunction:: ubw_string_unbox
.. doxygenfunction:: ubw_symbol_unbox
.. doxygenfunction:: ubw_keyword_unbox
.. doxygenfunction:: ubw_cfunc_unbox

Build configuration
===================

.. doxygengroup:: config_object
   :content-only:

Test suite
==========

.. doxygenfile:: object_test.c
