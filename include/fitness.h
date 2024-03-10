#include <mutex>
#include <stdio.h>
// #include "../include/Util/Profiler.hpp"

float calculateFitness(unsigned char *img_data, unsigned char *surface_data, int _width, int _height);

float calculateFitnessGL(
    unsigned char *img_data, unsigned char *surface_data, int _width, int _height);