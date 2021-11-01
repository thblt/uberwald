.. _api-core-stack-reference:

*****
Stack
*****

Data structures
===============

The table is held in a single

.. doxygenstruct:: ubw_stack
   :members:
   :undoc-members:

Functions
=========

.. doxygenfunction:: ubw_stack_init
.. doxygenfunction:: ubw_stack_push
.. doxygenfunction:: ubw_stack_fpush
.. doxygenfunction:: ubw_stack_peek
.. doxygenfunction:: ubw_stack_fpeek
.. doxygenfunction:: ubw_stack_pop
.. doxygenfunction:: ubw_stack_fpop

Configuration
=============

The stack is not configurable.

Test suite
==========

.. doxygenfile:: stack_test.c
