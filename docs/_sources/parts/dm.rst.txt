Data Memory Unit
################

This part is a basic 8-bit memory unit.

..  image:: /latex/dm.png
    :align: center
    :width: 300

..  csv-table::
    :header: Pin, Def, Description

    1, daddr, 16-bit address input
    2, din, 8-bit data in
    3, rw, 1-bit selector
    4, dout, 8-bit data output

Specification
*************

..  pylit-oz::
    :align: center
    :width: 500

    \begin{schema}{dm}
      name: \bf{String} \\
      daddr: \bf{uint16\_t} \\
      din: \bf{uint8\_t} \\
      rw: [0,1] \\
      dout: \bf{uin8\_t}
    \ST
      out' = sel? in1 : in2
    \end{schema}

Signature
*********

..  csv-table::
    :header:    Name, Interface
    :delim: |

    Constructor|dm(std::string name)
