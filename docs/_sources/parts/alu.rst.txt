Arithmetic-logic Unit
#####################

This part is the ALU unit. IT performs both 8-bit and 16-bit operations

..  image:: /latex/alu.png
    :align: center
    :width: 300

..  csv-table::
    :header: Pin, Def, Description

    1, op1, 16-bit operand 1
    2, op2, 16-bit operand 2
    3, aop, 4-bit selector
    4, res, 16-bit result
    5, Z, Zero status flag

Specification
*************

..  pylit-oz::
    :align: center
    :width: 500

    \begin{schema}{alu}
      name: \bf{String} \\
      op1: \bf{uint16\_t} \\
      op2: \bf{uint16\_t} \\
      aop: [0,1] \\
      res: \bf{uin16\_t}
    \ST
      res' = sel? in1 : in2
    \end{schema}

Signature
*********

..  csv-table::
    :header:    Name, Interface
    :delim: |

    Constructor|alu(std::string name)
