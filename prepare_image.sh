#!/bin/bash
if [ "$#" -ne 3 ]; then
        echo "Usage: ./prepare_image.sh input output height."
	echo "Requires imagemagick."
	exit 1
fi
convert $1  -colorspace gray -compress none -depth 8 -resize "x$3" "temp_$2".pgm
grep -v '^#' "temp_$2".pgm > $2 # removes comments 
rm "temp_$2".pgm
exit 0
