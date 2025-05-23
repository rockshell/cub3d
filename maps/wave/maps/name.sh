#!/bin/bash

# Check if a filename is provided as an argument
if [ -z "$1" ]; then
  echo "Usage: $0 <filename>"
  exit 1
fi

filename="$1"

# Check if the file exists
if [ ! -f "$filename" ]; then
  echo "Error: File '$filename' not found."
  exit 1
fi

# Use sed to replace .png with .png
sed -i 's/\.png/\.png/g' "$filename"

echo "Replaced '.png' with '.png' in '$filename'."
