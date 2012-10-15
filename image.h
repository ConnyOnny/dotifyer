#ifndef _IMAGE_H_
#define _IMAGE_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "error.h"

float* readImage (FILE *input, size_t* width, size_t* height);

float sample (float* image, size_t width, size_t height, float dotsize, float x, float y);

#endif
