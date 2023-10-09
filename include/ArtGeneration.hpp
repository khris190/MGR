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

class ArtGeneration {
private:
    Population population;
    int parent1;
    int parent2;

    void draw(cairo_surface_t* pImg, size_t index);

public:
    ArtGeneration(int childrenSize = 50, int genotypeSize = 64);
    void startEvolution(cairo_surface_t* pImg);
    ~ArtGeneration() = default;
};

#endif // ARTGENERATION_HPP