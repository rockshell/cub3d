for file in *.png; do
    magick "$file" "${file%.png}.png"
done
