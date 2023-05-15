#ifndef ARTGENERATION_HPP
#define ARTGENERATION_HPP

#include "Config.hpp"
#include "external_utils/BS_thread_pool_light.hpp"
#include "fitness.hpp"
#include "genetic/Genotype.hpp"
#include "my_utils/Logger.hpp"
#include "my_utils/Profiler.hpp"
#include <cairo/cairo.h>
#include <stdexcept>
#include <stdlib.h>
#include <thread>

class ArtGeneration
{
private:
    Genotype** pChildren_;
    int childrenSize_;
    int parent1_, parent2_;

    void CreateChildren(float mutationRate = 0.05f);
    void GenerateFirstPopulation(int childrenSize, int genotypeSize);
    void Draw(cairo_surface_t* pImg, size_t index);
    static void AsyncFitness(cairo_surface_t* img, Genotype** pChildren, volatile int* pBestIndexes,
      volatile float* pBestScores, int start, int stop, const int _width, const int _height);

public:
    ArtGeneration(int childrenSize = 50, int genotypeSize = 64);
    void StartEvolution(cairo_surface_t* pImg);
    ~ArtGeneration();
};

#endif // ARTGENERATION_HPP