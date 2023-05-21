#ifndef POPULATION_HPP
#define POPULATION_HPP

#include "Genotype.hpp"
#include <memory>
#include <utility>
#include <vector>
#include <cairo/cairo.h>
class Population
{
public:
    std::vector<float> scores;
    std::vector<std::pair<int, float>> bests;
    Population(int populationSize, int genotypeSize = 64);
    Population(Population&&) = default;
    Population(const Population&) = default;
    Population& operator=(Population&&) = default;
    Population& operator=(const Population&) = default;
    ~Population();

    void Cross(Genotype& parent1_, Genotype& parent2_);
    std::vector<Genotype> children;

    void CreateNextGeneration(int parent1_, int parent2_, float mutation_rate = 0.005f);
    void CreateNextGeneration(float mutation_rate = 0.005f);

    void DrawNFitness(cairo_surface_t* img);

    std::vector<std::pair<int, float>> getBest();

private:
};

#endif // POPULATION_HPP
