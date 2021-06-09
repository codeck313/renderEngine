for img in *.ppm; do
    filename=${img%.*}
    convert "$filename.ppm" "converted/$filename.png"
done
