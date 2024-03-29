
#ifndef FITNESS_HPP
#define FITNESS_HPP

#include "my_utils/Logger.hpp"
#include "my_utils/Profiler.hpp"
#include <cairo/cairo.h>

float fitness_v1_RGBA(unsigned char* pA, unsigned char* pB);
float fitness(cairo_surface_t* img, cairo_surface_t* surface);
float fitness(cairo_surface_t* img, unsigned char* surface);
float fitnessGL(cairo_surface_t* img, unsigned char* surface);

#endif // FITNESS_HPP
