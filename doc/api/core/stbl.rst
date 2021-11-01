.. _api-core-stbl-reference:

*******************
Symbol lookup table
*******************

A Lisp program is essentially made of symbols.  Symbols, being text,
are expensive to compute.  This is why they're internally represented
as numeric values, where each possible symbol is associated one, and
only one, numeric value.  (This means that during execution, symbols
are just qualified numbers).

The symbol table is an associative data structure mapping symbol
names (strings) to hashes and numeric identifiers.    When the
reader encounters a symbol, it calls ubw_stbl_intern() with that
symbol's name and receive a numeric ID.

Data structures
===============

The table is held in a single

.. doxygenstruct:: ubw_stbl
   :members:
   :undoc-members:

.. doxygenstruct:: ubw_symb
   :members:
   :undoc-members:

Functions
=========

.. doxygenfunction:: ubw_stbl_intern
.. doxygenfunction:: ubw_stbl_reverse

Configuration
=============

.. doxygentypedef:: ubw_symbhash

.. doxygendefine:: UBW_LISP_MAX_SYMBOL_LENGTH

Test suite
==========

.. doxygenfile:: stbl_test.c
