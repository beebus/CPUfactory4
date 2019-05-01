Decoder
#######

This part is the AVR instruction decoder. It takes two 16-bit inputs and
delivers several outputs based on the decoding logic.

The AVR instructions are usually contained in a single 16-bit code, but a few
instructions use a second 16-bit value to provide a constant to be used in the
instruction. In his implementation, we also provide the current value of the PC
used to fetch the instruction being decoded. If the instruciton does not use
the second word, then PC is incremented by one and passed on to the rest of the
machine. If the second word is needed, then PC is incremented by two before
being passed on.

..  image:: /latex/dec.png
    :align: center
    :width: 300

..  csv-table::
    :header: Pin, Def, Description

    1, ins1, 116-bit primary instruction code
    2, in2, 16-bit secondary instruction code (may not be used)
    4, out, 16-bit output

Specification
*************

..  pylit-oz::
    :align: center
    :width: 500

    \begin{schema}{dec}
      name: \bf{String} \\
      ins1: \bf{uint16\_t} \\
      ins2: \bf{uint16\_t} \\
      out: \bf{uin16\_t}
    \ST
      out' = sel? in1 : in2
    \end{schema}

Signature
*********

..  csv-table::
    :header:    Name, Interface
    :delim: |

    Constructor|dec(std::string name)
