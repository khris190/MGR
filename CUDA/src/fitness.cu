#include "../include/fitness.h"
#include "my_utils/Profiler.hpp"

static unsigned char* x = nullptr;
static std::mutex mxX;
__global__ void fitness_v1_RGBA2(int n, unsigned char* pA, unsigned char* pB)
{
    int i = threadIdx.x + blockIdx.x * blockDim.x;
    if (i < n) {
        float absR = fabsf(pA[i * 4 + 0] - pB[i * 4 + 0]);
        float absG = fabsf(pA[i * 4 + 1] - pB[i * 4 + 1]);
        float absB = fabsf(pA[i * 4 + 2] - pB[i * 4 + 2]);
        float absA = fabsf(pA[i * 4 + 3] - pB[i * 4 + 3]);
#define AlphaMulti 1.0f
        float val2 = (absR + absG + absB) + absA * AlphaMulti;
        val2 = (float)(255.f - val2 / (3.f + AlphaMulti)) / 255.f;
        memcpy(&pB[(i)*4], &val2, sizeof(float));
    }
}

// Offloads a lot of addition of scores offset times to gpu
__global__ void calculateFitnessFromArray(int offset, float* arr, size_t size)
{
    int i = threadIdx.x + blockIdx.x * blockDim.x;
    i *= offset;
    if (i < size - offset) {
        for (size_t y = 1; y < offset; y++) {
            arr[i] += arr[i + y];
        }
        // arr[i] /= offset;
    }
}
float calculateFitness(unsigned char* img_data, unsigned char* surface_data, int _width, int _height)
{

    unsigned char* test;
    // Allocate Unified Memory – accessible from CPU or GPU
    int size = _width * _height;
    mxX.lock();
    if (x == nullptr) {
        cudaMallocManaged(&x, 4 * size * sizeof(unsigned char));
        cudaMemcpy(x, img_data, 4 * size, cudaMemcpyDefault);
    }
    mxX.unlock();
    cudaMallocManaged(&test, 4 * size * sizeof(unsigned char));

    cudaMemcpy(test, surface_data, 4 * size, cudaMemcpyDefault);

    {
        // newTimer("calculate fitness_v1_RGBA2");
        fitness_v1_RGBA2<<<_width, _height>>>(size, x, test);
        cudaError_t ce = cudaGetLastError();
        cudaDeviceSynchronize();
    }
    // increasing of this number lowers calculate fitness cpu timings 2 times and increases calculateFitnessFromArray 4
    // times, so its important to think about those numbers
    const short offset = 64;
    short rest = size % offset;
    size_t amount = (size - rest) / offset;
    size_t threadAmount = sqrt(amount) + 1;

    {
        // newTimer("calculateFitnessFromArray");
        calculateFitnessFromArray<<<threadAmount, threadAmount>>>(offset, (float*)test, size);
        cudaError_t ce = cudaGetLastError();
        cudaDeviceSynchronize();
    }

    double result = 0;
    float tmp_fitness = 0;
    {
        // newTimer("calculate fitness cpu");
        {
            for (int i = 0; i < amount; i++) {
                memcpy(&tmp_fitness, (void*)(test + 4 * i * offset), sizeof(float));
                result += tmp_fitness;
            }
            for (size_t i = 0; i < rest; i++) {
                memcpy(&tmp_fitness, (void*)(test + amount * offset * 4 + i * 4), sizeof(float));
                result += tmp_fitness;
            }
            result /= size;
        }
    }

    // Free memory
    cudaFree(test);
    return (result);
}