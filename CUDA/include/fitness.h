#include <stdio.h>
#include <mutex>
// #include "../include/Util/Profiler.hpp"

static unsigned char *x = nullptr;
static std::mutex mxX;

float calculateFitness(unsigned char *img_data, unsigned char *surface_data, int _width, int _height);