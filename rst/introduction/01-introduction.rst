Introduction
############

..  vim:filetype=rst spell:
..  include::   /header.inc

This project is designed to help students understand how modern processors
work. The "factory" here forms the basis for building a CPU simulator based on
some very simple concepts.

The project assumes that students have completed a first course in C++, and are
familiar with writing class files. They will need to know something about
inheritance, and be able to use a few data structures available in the ``C++
Standard Template Library`` as well. 

..  note::

    These more advanced concepts in C++ are kept to a minimum, and help on
    anything not normally covered in a first course in C++ is provided in the
    Appendix.

Student projects will consist of writing class files for the various components
needed to complete a simulator. They will also need to study the simple example
system provided here to build a complete machine using this factory. In this
factory, the final machine will be assembled from the student class files using
a JSON data file that controls assembling the parts at runtime. The example
code provided in this faactory shows how this is done for an example
simulation.

..  warning::

    This project is incomplete by design. Providing a full system defeats the
    educational value of the projects. This is a framework, to be completed by
    students.

