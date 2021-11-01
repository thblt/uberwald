.. _api-core--overview:

********
Overview
********

This document is a rough overview of the general design of Überwald.
It begins by describing the different components, how they're
implemented (to some extent, the ultimate truth is always the source
code) and most importantly how they all fit together.

Überwald is a Lisp interpreter.  Lisps are a family of programming
languages without multiple unique, defining features, one of which is
of particular interest from the interpreter standpoint:
**homoiconicity**.  Homoiconicity means that the internal
representation of a Lisp program is the same as the internal
representation of any piece of data.  To put it simply: a Lisp
interpreter is, by nature, a data deserializer.

A Lisp program is a sequence of **forms**.  A form may be either an
**atom**, like a number, a symbol or a keyword, or it may be a
**S-expression**, that is, one or more forms (recursive definition!)
enclosed within parentheses.  Running a Lisp program (in any Lisp
dialect!) means looping over two simple steps: read/evaluate, until
there are no more forms to read.

You may have already noticed a small originality here: Lisp machines
don't fully load a file *before* they begin evaluating it.  Instead,
the unit a processing is the form.  Why does this matter?  Because
Lisp is a highly dynamic language, where the whole interpreter is
exposed to the program in multiple ways.  A form may introduce a
reader macro to introduce new syntax, or it may even completely
replace the reader function, deeply modifying the syntax and semantics
of the language.

With this in mind, let's begin this tour of the Überwald internals.

.. contents::

Components
==========

This section describes what a Lisp interpreter is made of.

The Lisp object
---------------

At the beginning was something, and something was a Lisp object.
Because Lisp is a dynamically typed language, we need a generic
"object" which could store both a *type* and a *value*.  To that end, we use a
struct with two fields:

 1. A ``type`` field, whose type is an anonymous enum of primitive
    types (``LIST``, ``VECTOR``, ``INTEGER``, etc.);

 2. An anonymous field whose type is an anonymous union of the
    underlying C types: ``int``, ``double``, ``ubw_list``, etc.

    .. note:: The underlying types are configurable, so it's
              not guaranteed that Lisp integers be C ints, Lisp floats
              C doubles, etc.

Exactly two of these underlying types make the type recursive: a
**list** is represented as a pair of pointers to Lisp objects,
making up respectively the first element and the rest of the list; a
vector points to an :c:type:`ubw_vector`, which holds a pointer to a
memory area holding other objects.

It is important to understand that :c:type:`ubw_obj` can represent
every possible value that can exist in a Lisp program.  Since the type
is partially recursive, it is not limited in data length, yet has a
fixed size, which makes it easy to address in memory.

.. @TODO Finalize

See :ref:`api-core-object-reference` for complete formal documentation.


Memory management, part 1: the heap
-----------------------------------

Now that we have a representation of Lisp objects, we need to put them
somewhere.  Because in Lisp, memory is managed automatically
(garbage-collected), we can't just play around with ``malloc()``,
since that means a program running for long enough will ultimately
take over the full memory.

Überwald's heap module does exactly
that.  It doesn't handle garbage collection itself, but puts in place
the essential part of garbage collection, that is, knowledge of memory
usage.

The heap is defined as:

It's actually quite simple: we have a start and a end, and a list of
"holes", that is, of free contiguous areas.

The reader
----------

We now have a way to represent Lisp objects, and to actually store
them in memory.  The obvious next step is to actually read Lisp
objects from Lisp code.  This is what a **reader** does.

Before we dive into the reader, remember that one of the defining
features of Lisp is **homoiconicity**, that is, representation of code is
the same as representation of data: a Lisp program is an ordered set
of Lisp lists.  This is why we don't need anything to read code, since
code is indistinguishable from data.

The reader looks like this:

.. doxygenfunction:: ubw_read
   :outline:

.. @TODO Link to discussion on runtime and symbol table

Notice that the type of its first two arguments is still unknown to
us.  The first one holds a pointer the runtime, which will be
discussed later, but is nothing more than a stack, a heap controller,
a symbol table, etc.  "Runtime" is a convenience name for wrapping all
these together, since they're highly interdependent anyway.

The second argument is a reader object, which is nothing more than a
position tracker and a status indication:

.. doxygenstruct:: ubw_reader
   :outline:

.. @TODO correctly link to header field

The reader reads ``buf`` as input text, and returns a pointer to a
:c:type:`ubw_obj`.  There's a catch, though: before using the return
value, the user must inspect the ``err`` field and make sure its value
is ``DONE``; any other value indicate an error and that the return
value is unusable.

The reader reads at most one form, and doesn't try to exhaust input
data (it will detect premature EOF, though).  After :c:func:`ubw_read`
returns, the  ``pos`` field of the reader will hold the index of the
character immediately following the one that's been read.  This is
important when evaluating files, since these usually contain more than
one form.

No we can read Lisp code, and we'll soon be evaluating it.

The environment
---------------

One of the most common features of programming languages is to
associate values to symbols, and Lisps are no exception.  This
involves two components: the environment, which manage bindings and
shadowing, and the symbol table.

The environment is actually a list of environments, since an
environment is a combination of a list of bindings and a pointer to a
parent:

.. doxygenstruct:: ubw_env
   :no-link:

At each point in the execution of the program, there's one and only one
head environment.  Looking up a symbol in an environment

The symbol table
----------------

Like the ephemeral store, the symbol table is a performance
optimization feature, but is not strictly required: a Lisp interpreter
could perfectly well treat its symbols as strings, although this would
mean a severe performance penalty.  In Überwald (and most Lisp
machines), when the interpreter encounters a symbol, it looks it up in
the symbol table, which is simply an association list of strings and
integers.  The symbol table holds an array of:

.. doxygenstruct:: ubw_symb
   :no-link:

A unique identifier, a hash and a string.  The table is sorted by
hash.  Looking up a symbol is simply a matter of performing a binary
search, and determining if the symbol is already in the table.  If it
isn't, it's inserted at its place, by increasing order of hash.

**What about keywords?** A keyword and an object have the exact same
internal representation, a :c:type:`ubw_symbid`.  They differ in how
they're evaluated, but they're stored the same way in the same symbol
table.

The evaluator
-------------

The stack
^^^^^^^^^
