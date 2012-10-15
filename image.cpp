#include "image.h"

int fpeek(FILE *stream) {
	int c;
	c = fgetc(stream);
	ungetc(c, stream);
	return c;
}

void eatLine (FILE *stream) {
	int c;
	do {
		c = fgetc(stream);
	} while (c!='\n' && c!=EOF);
}

float* readImage (FILE *input, size_t *width, size_t *height) {
	char sbuf [512];
	size_t readWidth=0, readHeight=0;
	int readChars;
	size_t colorCount=0; /* this is integer, but always used as double */
	sbuf[0]=0;
	readChars = fscanf(input, "%512s", sbuf);
	if (readChars != 1)
		ERROR("Could not read anything from file\n");
	if (strcmp(sbuf,"P5"))
		ERROR("Expected pgm binary file (P5) but header was \"%s\"\n", sbuf);
	while (fpeek(input) == '#' || fpeek(input) == '\n') {
		eatLine (input);
	}
	readChars = fscanf(input, "%512zu", &readWidth);
	if (readChars != 1)
		ERROR("could not read image width\n");
	readChars = fscanf(input, "%512zu", &readHeight);
	if (readChars != 1)
		ERROR("could not read image width\n");
	if (readWidth <= 0 || readHeight <= 0)
		ERROR("Invalid image file with nonpositive dimensions\n");
	readChars = fscanf(input, "%512zu", &colorCount);
	if (readChars != 1)
		ERROR("could not read color count\n");
	if (colorCount <= 1)
		ERROR("Invalid image file with color count <= 1\n");
	if (colorCount > 255)
		/* that would be nasty multi-byte stuff */
		ERROR("This program does not support images with more than 256 colors.\n");
	if (!isspace(fgetc(input))) {
		ERROR("Invalid image file\n");
	}
	/* init memory */
	float * data = (float*)malloc (readWidth*readHeight*sizeof(float));
	*width = readWidth;
	*height = readHeight;
	/* read data */
	for (size_t y=0; y<readHeight; y++) {
		for (size_t x=0; x<readWidth; x++) {
			int got = fgetc (input);
			if (got == EOF)
				ERROR ("image file incomplete\n");
			data[x+y*readWidth] = (float)got / (colorCount-1);
		}
	}
	if (fgetc(input) != EOF) {
		fprintf(stderr,"WARNING: unexpected data at end of file.\n");
	}
	return data;
}

float min (float a, float b) {
	return a<b?a:b;
}

float max (float a, float b) {
	return a>b?a:b;
}

float average (float* image, size_t width, size_t height, size_t top, size_t left, size_t bottom, size_t right) {
	double count = (bottom-top+1) * (right-left+1);
	double result = 0;
	for (size_t y=top; y<=bottom; y++) {
		for (size_t x=left; x<=right; x++) {
			result += image[x+y*width];
		}
	}
	return min(1.0f,max(result/count,0.0f));
}

size_t min (size_t a, size_t b) {
	return a<b?a:b;
}

size_t max (size_t a, size_t b) {
	return a>b?a:b;
}

float sample (float* image, size_t width, size_t height, float dotsize, float x, float y) {
	if (x>=width || y>=height || x<0 || y<0)
		ERROR("out of bounds: %f, %f\n", x, y);
	size_t top = max(0,(size_t)(y-dotsize/2));
	size_t left = max(0,(size_t)(x-dotsize/2));
	size_t bottom = min(height-1,(size_t)(y+dotsize/2));
	size_t right = min(width-1,(size_t)(x+dotsize/2));
	return average (image, width, height, top, left, bottom, right);;
}
