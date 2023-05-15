#ifndef GENOTYPE_HPP
#define GENOTYPE_HPP

#include "Gene.hpp"
#include "common/DataStructures.hpp"
#include "common/Randoms.hpp"
#include "my_utils/Logger.hpp"
#include <cairo/cairo.h>
#include <memory.h>
#include <stdlib.h>
#include <tgmath.h>

// TODO move drawing functions and get an dependency injection going
class Genotype
{
public:
    int size;
    Gene* gene_arr;
    Genotype(int size_ = 64);
    void SwapAll(float mutation_rate = 0.001f);
    void SwapOne(float mutation_rate = 0.001f, int i = -1);
    void Mutate(float mutation_rate = 0.001f);
    void Wiggle(float mutation_rate = 0.001f);
    void Cross(Genotype* parent1_, Genotype* parent2_);
    void Draw(cairo_surface_t* img, float scale = 0.5f);
    ~Genotype();
};

#endif // GENOTYPE_HPP
