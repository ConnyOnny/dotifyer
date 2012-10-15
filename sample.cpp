#include "sample.h"

void samples (size_t width, size_t height, size_t dotsize, float ** xcoords, float ** ycoords, size_t * samples) {
	size_t rwidth = width/dotsize;
	size_t rheight = height/dotsize;
	*samples = rwidth*rheight - rheight/2;
	*xcoords = (float*) malloc (*samples*sizeof(float));
	*ycoords = (float*) malloc (*samples*sizeof(float));
	size_t i = 0;
	for (size_t y=0; y<rheight; y++) {
		int odd = y%2;
		for (size_t x=0; x<rwidth-(odd?1:0); x++) {
			(*xcoords)[i] = (x + 0.5f + (odd?0.5f:0.0f)) * dotsize;
			(*ycoords)[i] = (y + 0.5f) * dotsize;
			i++;
		}
	}
}

void samples_plain (size_t width, size_t height, size_t dotsize, float ** xcoords, float ** ycoords, size_t * samples) {
	*xcoords = (float*) malloc (width*height/(dotsize*dotsize)*sizeof(float));
	*ycoords = (float*) malloc (width*height/(dotsize*dotsize)*sizeof(float));
	*samples = width*height/(dotsize*dotsize);
	size_t i = 0;
	for (size_t y=0; y<height/dotsize; y++) {
		for (size_t x=0; x<width/dotsize; x++) {
			(*xcoords)[i] = (x + 0.5f) * dotsize;
			(*ycoords)[i] = (y + 0.5f) * dotsize;
			i++;
		}
	}
}
