#ifndef POPULATION_HPP
#define POPULATION_HPP

#include "Genotype.hpp"
#include <memory>
#include <vector>
class Population
{
public:
    Population(int populationSize, int genotypeSize = 64);
    Population(Population&&) = default;
    Population(const Population&) = default;
    Population& operator=(Population&&) = default;
    Population& operator=(const Population&) = default;
    ~Population();

    void Cross(Genotype& parent1_, Genotype& parent2_);
    std::vector<Genotype> children;

    void CreateNextGeneration(int parent1_, int parent2_, float mutation_rate = 0.05f);

private:
};

#endif // POPULATION_HPP
