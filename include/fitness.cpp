
#include "fitness.hpp"
// https://learn.microsoft.com/en-us/cpp/cpp/welcome-back-to-cpp-modern-cpp?view=msvc-170
extern float calculateFitness(unsigned char* img_data, unsigned char* surface_data, int _width, int _height);
extern float calculateFitnessGL(
  unsigned char* img_data, unsigned char* surface_data, int _width, int _height, bool old = false);

float fitness_v1_RGBA(unsigned char* pA, unsigned char* pB)
{
    auto absR = (float)std::abs(pA[0] - pB[0]);
    auto absG = (float)std::abs(pA[1] - pB[1]);
    auto absB = (float)std::abs(pA[2] - pB[2]);
    auto absA = (float)std::abs(pA[3] - pB[3]);
    auto val2 = (absR + absG + absB) + absA;
    return (float)(255.f - val2 / 4.f) / 255.f;
}

float fitness(cairo_surface_t* img, cairo_surface_t* surface)
{
    newTimer("fitness function timer");
    unsigned char* img_data = cairo_image_surface_get_data(img);
    unsigned char* surface_data = cairo_image_surface_get_data(surface);

    int _width, _height;

    _width = cairo_image_surface_get_width(img);
    _height = cairo_image_surface_get_height(img);

    float ret = calculateFitness(img_data, surface_data, _width, _height);
    return ret;

    // int temp_offset;
    // int offset = _width * _height;
    // float tmp_fitness = 0, row_fitness = 0, img_fitness = 0;

    // for (size_t y = 0; y < _height; y++)
    // {
    //     for (size_t x = 0; x < _width; x++)
    //     {
    //         temp_offset = y * _width + x;

    //         tmp_fitness += fitness_v1_RGBA(img_data + temp_offset * 4, surface_data + temp_offset * 4);
    //         row_fitness += tmp_fitness;
    //         tmp_fitness = 0;
    //     }
    //     row_fitness /= _width;
    //     img_fitness += row_fitness;
    //     row_fitness = 0;
    // }
    // img_fitness /= _height;
    // return img_fitness;
}
float fitnessGL(cairo_surface_t* img, unsigned char* surface)
{
    newTimer("fitnessGL function timer");
    unsigned char* img_data = cairo_image_surface_get_data(img);

    int _width, _height;

    _width = cairo_image_surface_get_width(img);
    _height = cairo_image_surface_get_height(img);

    float ret = calculateFitnessGL(img_data, surface, _width, _height);
    return ret;
}
