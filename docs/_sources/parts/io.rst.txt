Memory Mapped IO
################

This part models the IO address space of the AVR

..  image:: /latex/io.png
    :align: center
    :width: 300

..  csv-table::
    :header: Pin, Def, Description

    1, port, 8-bit port selector
    2, in, 8-bit data value to output
    3, rw, 1-bit selector
    4, out, 8-bit input receive data

Specification
*************

..  pylit-oz::
    :align: center
    :width: 500

    \begin{schema}{io}
      name: \bf{String} \\
      in1: \bf{uint16\_t} \\
      in2: \bf{uint16\_t} \\
      sel: [0,1] \\
      out: \bf{uin16\_t}
    \ST
      out' = sel? in1 : in2
    \end{schema}

Signature
*********

..  csv-table::
    :header:    Name, Interface
    :delim: |

    Constructor|mux2(std::string name)
