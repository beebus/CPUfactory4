Register File
#############

This part models a two port read/one port write register file, with 32 8-bit
registers. It also supports 16-bit read and write using the top 6 registers.


..  image:: /latex/rf.png
    :align: center
    :width: 300

..  csv-table::
    :header: Pin, Def, Description

    1, in1, 16-bit input 1
    2, in2, 16-bit input 2
    3, sel, 1-bit selector
    4, out, 16-bit output

Specification
*************

..  pylit-oz::
    :align: center
    :width: 500

    \begin{schema}{muxa}
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
