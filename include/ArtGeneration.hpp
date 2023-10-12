#ifndef ARTGENERATION_HPP
#define ARTGENERATION_HPP

#include "common/Config.hpp"
#include "genetic/Population.hpp"

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