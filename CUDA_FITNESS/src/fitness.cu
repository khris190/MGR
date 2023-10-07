#include "../include/fitness.h"
#include "my_utils/Profiler.hpp"
#include <exception>

static unsigned char* x = nullptr;
static std::mutex mxX;
__global__ void fitness_v1_RGBA2(int n, unsigned char* pA, unsigned char* pB)
{
    int i = threadIdx.x + blockIdx.x * blockDim.x;
    if (i < n) {
        // brga to rgba
        float absR = fabsf(pA[i * 4 + 0] - pB[i * 4 + 2]);
        float absG = fabsf(pA[i * 4 + 1] - pB[i * 4 + 1]);
        float absB = fabsf(pA[i * 4 + 2] - pB[i * 4 + 0]);
        float absA = fabsf(pA[i * 4 + 3] - pB[i * 4 + 3]);
#define AlphaMulti 1.f
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

    cudaMallocManaged(&test, 4 * size * sizeof(unsigned char));

    cudaMemcpy(test, surface_data, 4 * size, cudaMemcpyDefault);
    float result = calculateFitnessGL(img_data, test, _width, _height);
    // Free memory
    cudaFree(test);
    return (result);
}

float calculateFitnessGL(unsigned char* img_data, unsigned char* surface_data, int _width, int _height)
{
    // newTimer("calculateFitnessGL");
    int size = _width * _height;
    mxX.lock();
    if (x == nullptr) {
        cudaMallocManaged(&x, 4 * size * sizeof(unsigned char));
        cudaMemcpy(x, img_data, 4 * size, cudaMemcpyDefault);
    }
    mxX.unlock();
    {
        // newTimer("calculate fitness_v1_RGBA2");
        fitness_v1_RGBA2<<<_width, _height>>>(size, x, surface_data);
        cudaError_t ce = cudaGetLastError();
        if (ce != cudaSuccess) {
            throw std::runtime_error(cudaGetErrorString(ce));
        }
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
        calculateFitnessFromArray<<<threadAmount, threadAmount>>>(offset, (float*)surface_data, size);
        cudaError_t ce = cudaGetLastError();
        if (ce != cudaSuccess) {
            throw std::runtime_error(cudaGetErrorString(ce));
        }
        cudaDeviceSynchronize();
    }

    double result = 0;
    float tmp_fitness = 0;
    if (true) {
        {
            newTimer("calculate fitness cpu");
            {
                for (int i = 0; i < amount; i++) {
                    memcpy(&tmp_fitness, (void*)(surface_data + 4 * i * offset), sizeof(float));
                    result += tmp_fitness;
                }
                for (size_t i = 0; i < rest; i++) {
                    memcpy(&tmp_fitness, (void*)(surface_data + amount * offset * 4 + i * 4), sizeof(float));
                    result += tmp_fitness;
                }
                result /= size;
            }
        }
        return (result);
    }
    float tempSurface[size];
    // newTimer("calculate fitness cpu and mem cpy");
    cudaMemcpy(tempSurface, surface_data, size * sizeof(float), cudaMemcpyDefault);
    {
        {
            for (int i = 0; i < amount; i++) {
                result += tempSurface[i * offset];
            }
            for (size_t i = 0; i < rest; i++) {
                result += tempSurface[amount * offset + i];
            }
            result /= size;
        }
    }
    return (result);
}