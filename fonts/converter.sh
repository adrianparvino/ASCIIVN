#!/usr/bin/env bash

# USAGE: convert [fontname] [fontsize]
# OUTPUT: A directory named fontname-fontsize with png children

mkdir ${1}-${2}
cd ${1}-${2}

for i in 'c' 'l' 'o' '|' ',' '!' '.' 't' 'T' 'x' 'X' 'Y'; do
convert -font $1 -pointsize $2 "label:${i}" "${i}.png";
done
convert -font $1 -pointsize $2 label:/ slash.png;
convert -font $1 -pointsize $2 label:$ \$.png;
convert -font $1 -pointsize $2 label:\\\\ \\.png;
convert -font $1 -pointsize $2 label:\\\  \ .png;
