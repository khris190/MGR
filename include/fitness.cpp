
#include "fitnessCu.h"
#include "fitness.hpp"
float fitness_v1_RGBA(const unsigned char *pA, const unsigned char *pB)
{
    auto absR = (float)std::abs(pA[0] - pB[0]);
    auto absG = (float)std::abs(pA[1] - pB[1]);
    auto absB = (float)std::abs(pA[2] - pB[2]);
    auto absA = (float)std::abs(pA[3] - pB[3]);
    auto val2 = (absR + absG + absB) + absA;
    return (255.f - val2 / 4.f) / 255.f;
}

float cpuFitness(unsigned char *img, unsigned char *surface, int width, int height)
{
    int temp_offset;
    int offset = width * height;
    float tmp_fitness = 0, row_fitness = 0, img_fitness = 0;

    for (size_t y = 0; y < height; y++)
    {
        for (size_t x = 0; x < width; x++)
        {
            temp_offset = y * width + x;

            tmp_fitness += fitness_v1_RGBA(img + temp_offset * 4, surface + temp_offset * 4);
            row_fitness += tmp_fitness;
            tmp_fitness = 0;
        }
        row_fitness /= width;
        img_fitness += row_fitness;
        row_fitness = 0;
    }
    img_fitness /= height;
    return img_fitness;
}

float fitness(cairo_surface_t *img, cairo_surface_t *surface)
{
    return fitness(img, cairo_image_surface_get_data(surface));
}
float fitness(cairo_surface_t *img, unsigned char *surface)
{

    unsigned char *imgData = cairo_image_surface_get_data(img);

    int width = cairo_image_surface_get_width(img);
    int height = cairo_image_surface_get_height(img);
    float ret;

    ret = cpuFitness(imgData, surface, width, height);
    // try
    // {
    //     ret = calculateFitness(imgData, surface, width, height);
    // }
    // catch (const std::exception &e)
    // {
    //     ret = cpuFitness(imgData, surface, width, height);
    // }

    return ret;
}
