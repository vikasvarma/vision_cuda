#include "../sobel/sobel.h"
#include "../rgb2gray/rgb2gray.h"
#include "../image/image.h"
#include "cuda_runtime.h"
#include <iostream>

int main()
{
    const char *lenna = "C:\\Projects\\cuda\\edge\\data\\lenna.png";
    Image rgb(lenna);
    Image gray(rgb.W, rgb.H, 1);
    rgb2gray(rgb, gray);
    gray.write("gray.png");
    return 0;
}