Instruction Memory
##################

This part is a 16-bit instruction memory unit.

..  image:: /latex/im.png
    :align: center
    :width: 300

..  csv-table::
    :header: Pin, Def, Description

    1, pc, 16-bit pc address
    2, ins1, 16-bit instruction
    3, ins2, 16-bit optional constant

Specification
*************

..  pylit-oz::
    :align: center
    :width: 500

    \begin{schema}{im}
      name: \bf{String} \\
      pc: \bf{uint16\_t} \\
      ins1: \bf{uint16\_t} \\
      ins2: \bf{uint16\_t} \\
    \ST
      ins1' = im[pc]
      ins2' = im[pc+1]
    \end{schema}

Signature
*********

..  csv-table::
    :header:    Name, Interface
    :delim: |

    Constructor|im(std::string name)
