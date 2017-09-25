#!/bin/bash
# create multiresolution windows icon
ICON_SRC=../../src/qt/res/icons/arepacoin.png
ICON_DST=../../src/qt/res/icons/arepacoin.ico
convert ${ICON_SRC} -resize 16x16 arepacoin-16.png
convert ${ICON_SRC} -resize 32x32 arepacoin-32.png
convert ${ICON_SRC} -resize 48x48 arepacoin-48.png
convert arepacoin-48.png arepacoin-32.png arepacoin-16.png ${ICON_DST}

