#!/bin/bash

# Check if imagemagick is installed
if ! command -v convert &> /dev/null; then
  echo "Error: ImageMagick is not installed."
  echo "Please install ImageMagick to use this script."
  echo "  - On Debian/Ubuntu: sudo apt install imagemagick"
  echo "  - On Fedora/CentOS: sudo yum install ImageMagick"
  echo "  - On Arch Linux: sudo pacman -S imagemagick"
  exit 1
fi

# Loop through all files in the current directory
for file in *.xpm; do

  # Extract the filename without the extension
  filename=$(basename "$file" .xpm)

  # Convert the xpm file to png
  convert "$file" "$filename.png"

  # Check if the conversion was successful
  if [ $? -eq 0 ]; then
    echo "Converted $file to $filename.png"
  else
    echo "Error converting $file"
  fi
done

echo "Conversion process complete."
