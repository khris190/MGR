#include "Population.hpp"
#include "genetic/Genotype.hpp"

Population::Population(int populationSize, int genotypeSize)
{
    this->children.reserve(populationSize);
    for (size_t i = 0; i < populationSize; i++) {
        this->children.push_back(Genotype(genotypeSize));
    }
}

void Population::CreateNextGeneration(int parent1_, int parent2_, float mutation_rate)
{
    for (size_t i = 0; i < this->children.size(); i++) {
        if (i != parent1_ && i != parent2_) {
            this->children[i].Cross(this->children[parent1_], this->children[parent2_]);
            this->children[i].Mutate(mutation_rate);
        }
    }
}

Population::~Population() { }