#!/usr/bin/env bash

DOT_DIR="DOTFiles"
PNG_DIR="PNGFiles"

#clean directories of PNG and DOT files
rm -rf "$PNG_DIR"
rm -rf "$DOT_DIR"


mkdir -p "DOTFiles"
mkdir -p "PNGFiles"

./exec


DOT_DIR="DOTFiles"
PNG_DIR="PNGFiles"
GIF_OUT="simulation.gif"

mkdir -p "$PNG_DIR"

for dotfile in "$DOT_DIR"/*.dot; do
    base=$(basename "$dotfile" .dot)
    dot -Tpng "$dotfile" -o "$PNG_DIR/$base.png"
done

FILES=( "$PNG_DIR"/*.png )
if [ ${#FILES[@]} -eq 0 ]; then
    echo "No PNG files found in $PNG_DIR/"
    exit 1
fi

DELAY=100
convert -delay "$DELAY" -loop 0 "${FILES[@]}" "$GIF_OUT"

echo "Created GIF: $GIF_OUT"
