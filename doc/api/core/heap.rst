.. _api-core-heap-reference:

===============
Heap controller
===============

Introduction
============

Manage the heap and the optional ephemeral store.

The ephemeral store
-------------------

The ephemeral store is a special part of the heap used by the
reader to store volatile values.  Unlike the regular heap, the
ephemeral store:

 - does not support deleting values, and is not garbage collected.

 - is allocated continuously, like a stack.  New values are stored
   on the slot next to the previous one.  This means it doesn't
   fragment.

 - is destroyed all-at-once, using a single global reference
   counter.  The counter gets increased by one by calling
   ubw_es_hold(), and decreased by one with ubw_es_release().  When
   it reaches zero, the head pointer is reset to the first slot and
   the store is back at full capacity.  If `UBW_DEBUG` is set, all
   values are also given the `_DELETED` type to help detecting
   uses-after-free.

Without ephemeral store, a 12-slots heap looks like::

       +-+-+-+-+-+-+-+-+-+-+-+-+
       | | | | | | | | | | | | |
       +-+-+-+-+-+-+-+-+-+-+-+-+
       ^_h                     ^_hend

With a 4-slots ephemeral store::

        __heap_________ __eph__
       !               !       !
       +-+-+-+-+-+-+-+-+-+-+-+-+
       | | | | | | | | | | | | |
       +-+-+-+-+-+-+-+-+-+-+-+-+
       ^_h             ^_es    ^_esend
                       ^_hend

Unlike the heap, the ephemeral store is allocated as a single block,
left to right, and is never fragmented.  New values are stored on the
first available slot,

Data structures
===============

.. doxygenstruct:: ubw_heap

Functions
=========

.. doxygenfunction:: ubw_heap_init

.. doxygenfunction:: ubw_new

.. doxygenfunction:: ubw_malloc


Test suite
----------

..
   doxygenfile:: heap_test.h
