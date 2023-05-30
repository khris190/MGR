#ifndef POPULATION_HPP
#define POPULATION_HPP

#include "Genotype.hpp"
#include <memory>
#include <utility>
#include <vector>
#include <cairo/cairo.h>
#include "common/Config.hpp"
#include "fitness.hpp"
#include "genetic/Genotype.hpp"
#include "drawing/openGL/openGLDrawer.hpp"
#include "my_utils/Profiler.hpp"
#include <sys/types.h>
#include <utility>
#include "external_utils/BS_thread_pool_light.hpp"
class Population
{
public:
    std::vector<float> scores;
    std::vector<std::pair<int, float>> bests;
    Population(int populationSize, int genotypeSize = 64);
    Population(Population&&) = delete;
    Population(const Population&) = delete;
    Population& operator=(Population&&) = delete;
    Population& operator=(const Population&) = delete;
    ~Population();

    void Cross(Genotype& parent1_, Genotype& parent2_);
    std::vector<Genotype> children;

    void CreateNextGeneration(int parent1_, int parent2_, float mutation_rate = 0.005f);
    void CreateNextGeneration(float mutation_rate = 0.005f);

    void DrawNFitness(cairo_surface_t* img);

    std::vector<std::pair<int, float>> getBest();

private:
    BS::thread_pool_light pool;
    std::vector<std::future<float>> workers;
};

#endif // POPULATION_HPP
