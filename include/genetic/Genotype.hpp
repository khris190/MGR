#ifndef GENOTYPE_HPP
#define GENOTYPE_HPP

#include "Gene.hpp"
#include "common/DataStructures.hpp"
#include "common/Randoms.hpp"
#include "my_utils/Logger.hpp"
#include <cairo/cairo.h>
#include <cstddef>
#include <memory.h>
#include <stdlib.h>
#include <tgmath.h>
#include <vector>

class Genotype {
public:
    std::vector<Gene> genes;

    size_t getSize() const;
    explicit Genotype(int size_ = 64);
    void swapAll(float mutationRate = 0.001f);
    void swapOne(float mutationRate = 0.001f, long i = -1);
    void mutate(float mutationRate = 0.001f);
    void wiggle(float mutationRate = 0.001f);
    void cross(Genotype& parent1, Genotype& parent2);
    void draw(cairo_surface_t* img, float scale = 0.5f) const;
    ~Genotype() = default;
};

#endif // GENOTYPE_HPP
