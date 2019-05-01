#!/usr/bin/env bash

genimage() {
	pdflatex $1.tex
	convert -density 300 $1.pdf -quality 90 $1.png
	rm $1.aux $1.log $1.pdf
}

for item in alu rf mux2 mux3 dec avrsim dm io stk
do
	genimage $item
done
