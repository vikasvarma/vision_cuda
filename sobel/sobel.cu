#include "sobel.h"
#include "cuda_runtime.h"

#define TILE_W = 16;
#define TILE_H = 16;

/*******************************************************************************
 * @brief _SOBEL - CUDA kernel for sobel edge detection filter.
 * const Image* src: Pointer to the source image.
 */
__global__ void _sobel(const Image& src, const Image& out)
{

}

Image &sobel(Image& src)
{
    return src;
}