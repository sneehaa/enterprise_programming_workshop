#include <stdio.h>
#include <stdlib.h>
#include <cuda_runtime.h>
#include "lodepng.h"

#define THREADS_PER_BLOCK 256
__global__ void grayscale_kernel(unsigned char* img, int num_pixels) {
    int idx = blockIdx.x * blockDim.x + threadIdx.x;

    if (idx < num_pixels) {
        int offset = 4 * idx;

        unsigned char r = img[offset];
        unsigned char g = img[offset + 1];
        unsigned char b = img[offset + 2];

        unsigned char gray = (r + g + b) / 3;

        img[offset]     = gray;
        img[offset + 1] = gray;
        img[offset + 2] = gray;
    }
}

int main() {
    unsigned char* image = NULL;
    unsigned width, height;

    unsigned error = lodepng_decode32_file(
        &image,
        &width,
        &height,
        "input.png"
    );

    if (error) {
        printf("Decode error %u: %s\n",
               error,
               lodepng_error_text(error));
        return 1;
    }

    int num_pixels = width * height;
    size_t bytes = num_pixels * 4 * sizeof(unsigned char);

    unsigned char* d_image;
    cudaMalloc((void**)&d_image, bytes);
    cudaMemcpy(d_image, image, bytes, cudaMemcpyHostToDevice);

    int blocks = (num_pixels + THREADS_PER_BLOCK - 1) / THREADS_PER_BLOCK;

    grayscale_kernel<<<blocks, THREADS_PER_BLOCK>>>(
        d_image,
        num_pixels
    );

    cudaDeviceSynchronize();

    cudaError_t err = cudaGetLastError();
    if (err != cudaSuccess) {
        printf("Kernel error: %s\n", cudaGetErrorString(err));
    }

    cudaMemcpy(image, d_image, bytes, cudaMemcpyDeviceToHost);

    error = lodepng_encode32_file(
        "grayscale_cuda.png",
        image,
        width,
        height
    );

    if (error) {
        printf("Encode error %u: %s\n",
               error,
               lodepng_error_text(error));
    } else {
        printf("Saved grayscale_cuda.png\n");
    }

    cudaFree(d_image);
    free(image);

    return 0;
}
