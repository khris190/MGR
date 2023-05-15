#ifndef ARTGENERATION_HPP
#define ARTGENERATION_HPP

#include "common/Config.hpp"
#include "external_utils/BS_thread_pool_light.hpp"
#include "fitness.hpp"
#include "genetic/Genotype.hpp"
#include "genetic/Population.hpp"
#include "my_utils/Logger.hpp"
#include "my_utils/Profiler.hpp"
#include <cairo/cairo.h>
#include <stdexcept>
#include <stdlib.h>
#include <thread>

class ArtGeneration
{
private:
    Population _population;
    int parent1_, parent2_;

    void Draw(cairo_surface_t* pImg, size_t index);
    static void AsyncFitness(cairo_surface_t* img, Population population, volatile int* best_indexes,
      volatile float* best_scores, int start, int stop, int _width, int _height);

public:
    ArtGeneration(int childrenSize = 50, int genotypeSize = 64);
    void StartEvolution(cairo_surface_t* pImg);
    ~ArtGeneration();
};

#endif // ARTGENERATION_HPP