#include "image.h"
#include "sample.h"

void drawHeader (size_t width, size_t height) {
	printf ("push graphic-context\nviewbox 0 0 %zu %zu\n", width, height);
}

void drawCircle (float posx, float posy, float radius) {
	printf ("circle %f,%f %f,%f\n", posx, posy, posx+radius, posy);
}

void drawFooter () {
	printf ("pop graphic-context");
}

int main (int argc, char** argv) {
	if (argc != 2 && argc != 3) {
		fprintf (stderr, "Usage:\n\t%s dotsize [radiusmultiplicator] < infile.pbm > outfile.mvg\n", argv[0]);
		exit (1);
	}
	int dotsize = atoi (argv[1]);
	if (dotsize < 1)
		ERROR ("dotsize must be positive\n");
	float radiusmul = argc > 2 ? atof (argv[2]) : 1.0f;
	size_t width, height;
	float *image;
	
	image = readImage (stdin, &width, &height);

	drawHeader(width, height);
	
	float *samplesx, *samplesy;
	size_t samplecount=0;



	samples(width,height,dotsize,&samplesx,&samplesy,&samplecount);

	if (samplecount < 1)
		ERROR ("Could not create samples\n");
	
	for (size_t i=0; i<samplecount; i++) {
		float brightness = sample(image,width,height,dotsize,samplesx[i],samplesy[i]);
		float r = (1.0f-brightness)*radiusmul*(dotsize/2.0f);
		drawCircle (samplesx[i], samplesy[i], r);
	}
	
	/*
	for (size_t y=0; y<height; y++) {
		for (size_t x=0; x<width; x++) {
			float r = (1.0f-image[x+y*width])*radiusmul*(dotsize/2.0f);
			float posx = (x + 0.5f) * dotsize;
			float posy = (y + 0.5f) * dotsize;
			drawCircle (posx, posy, r);
		}
	}*/
	drawFooter();
	exit(0);
}
