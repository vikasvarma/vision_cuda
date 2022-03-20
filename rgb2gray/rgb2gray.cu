#include <iostream>
#include "cuda_runtime.h"
#include "rgb2gray.h"

#define HANDLE_ERROR(err) (HandleError(err, __FILE__, __LINE__))
static void HandleError(cudaError_t err, const char *file, int line)
{
    if (err != cudaSuccess)
    {
        printf("%s in %s at line %d\n", cudaGetErrorString(err), file, line);
        exit(1);
    }
}

#define TILE_W 16
#define TILE_H 16

/*******************************************************************************
 * @brief rgb2gray_cuda - CUDA kernel for converting RGB images to grayscale.
 */
__global__ void rgb2gray_cuda(uint8_t *rgb, uint8_t *gray, int W, int H)
{
    // Get thread id wrt the entire image:
    int x = threadIdx.x + blockIdx.x * blockDim.x;
    int y = threadIdx.y + blockIdx.y * blockDim.y;

    //if ((x >= 0) && (y >= 0) && (x < W) && (y < H))
    //{
        auto p_r = rgb[y * W + x * 3 + 0];
        auto p_g = rgb[y * W + x * 3 + 1];
        auto p_b = rgb[y * W + x * 3 + 2];

        gray[y * W + x] = 0.30 * p_r + 0.59 * p_g + 0.11 * p_b;
    //}
}

/*******************************************************************************
 * @brief
 *
 */
__host__ void rgb2gray(Image &rgb, Image &gray)
{
    // TODO - Do some assertions for input parsing.
    int blockx, blocky;

    // Allocate memory for device buffers:
    uint8_t *d_in, *d_out;
    HANDLE_ERROR(cudaMalloc((void **)&d_in, rgb.bytes));
    HANDLE_ERROR(cudaMalloc((void **)&d_out, gray.bytes));

    // Copy data to the device buffers:
    HANDLE_ERROR(cudaMemcpy(d_in, rgb.data, rgb.bytes, cudaMemcpyHostToDevice));

    // Define kernel parameters:
    blockx = (rgb.W + TILE_W - 1) / TILE_W;
    blocky = (rgb.H + TILE_H - 1) / TILE_H;
    dim3 threads(TILE_W, TILE_H);
    dim3 blocks(blockx, blocky);

    // Process on the GPU
    rgb2gray_cuda<<<blocks, threads>>>(d_in, d_out, gray.W, gray.H);

    // Copy grayscale image back to host:
    HANDLE_ERROR(cudaMemcpy(gray.data, d_out, gray.bytes, cudaMemcpyDeviceToHost));

    cudaFree(d_in);
    cudaFree(d_out);
}