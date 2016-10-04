# dotifyer
converts greyscale images to black and white images made out of dots (in a vector format)

Here is a blog post about it, including images: https://cberhard.wordpress.com/2012/10/15/dotifyer

# usage
    dotsize [radiusmultiplicator] < infile.pgm > outfile.mvg

The input must be a portable gray map of type P5.
The output will be in mvg format ("magick vector graphic").
You can use imagemagick to convert it to svg or a raster format.
Radiusmultiplicator is 1.0 by default.
When its value is large, it allows for neighboring circles to overlap more.
