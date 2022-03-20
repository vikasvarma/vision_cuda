#ifndef RGB2GRAY_H
#define RGB2GRAY_H

#include "cuda_runtime.h"
#include "../image/image.h"

void rgb2gray(Image &rgb, Image &gray);

#endif