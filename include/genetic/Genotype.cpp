#include "Genotype.hpp"
#include "common/DataStructures.hpp"
#include "common/Randoms.hpp"
#include "genetic/Gene.hpp"
#include "my_utils/Profiler.hpp"
#include <array>
#include <cairo/cairo.h>
#include <cmath>
#include <cstddef>
#include <stdexcept>
#include <stdlib.h>
#include <tgmath.h>
#include <vector>

size_t Genotype::getSize() const { return genes.size(); }

Genotype::Genotype(int size)
{
    this->genes.reserve(size);
    for (size_t i = 0; i < size; i++) {
        this->genes.emplace_back();
        this->genes[i].randomize();
    }
}

// randomly swap all shapes order
void Genotype::swapAll(float mutationRate)
{
    for (long i = 0; i < genes.size(); i++) {
        this->swapOne(mutationRate, i);
    }
}

// randomly swap one shapes order
void Genotype::swapOne(float mutationRate, long i)
{
    if (i < 0) {
        i = rand() % genes.size();
    }
    if (fRand() <= mutationRate * 0) {
        int swap = rand() % genes.size() - 1;
        if (swap >= i) {
            swap += 1;
        }

        Gene tmp = genes[i];
        genes[i] = genes[swap];
        genes[swap] = tmp;
    }
}

void Genotype::mutate(float mutationRate)
{
    for (auto& gene : genes) {
        gene.mutate(mutationRate);
    }

    // SwapOne( mutationRate);
}

void Genotype::cross(Genotype& parent1, Genotype& parent2)
{
    if (parent1.genes.size() != parent2.genes.size()) {
        throw std::runtime_error { "parents size mismatch" };
    }
    for (size_t i = 0; i < parent1.genes.size(); i++) {
        if (rand() % 2) {
            this->genes[i] = parent1.genes[i];
        } else {
            this->genes[i] = parent2.genes[i];
        }
    }
}

//???
inline myData::position rotate(float x, float y, float angle)
{
    return myData::position(x * cos(angle) - y * sin(angle), x * sin(angle) + y * cos(angle));
}

void Genotype::draw(cairo_surface_t* img, float scale) const
{
    newTimer("olddrawing");
    cairo_t* cr = nullptr;
    for (auto const& gene : this->genes) {

        int width = cairo_image_surface_get_width(img);
        int height = cairo_image_surface_get_height(img);

        // #pragma GCC diagnostic push
        // #pragma GCC diagnostic ignored "-Wnarrowing"

        std::array<float, 4> color = { gene.color.r, gene.color.g, gene.color.b, gene.color.a };

        // #pragma GCC diagnostic pop

        auto x = static_cast<int>(gene.position.x * static_cast<float>(width));
        auto y = static_cast<int>(gene.position.y * static_cast<float>(height));

        float scaleX = gene.scale.x * static_cast<float>(width) * scale;
        float scaleY = gene.scale.y * static_cast<float>(height) * scale;
        auto rotation = static_cast<float>(gene.rotation * 3.14);

        cr = cairo_create(img);
        cairo_set_source_rgba(cr, color[0], color[1], color[2], color[3]);
        myData::position p1;
        myData::position p2;
        if (rotation != 0) {
            p1 = rotate(scaleX, scaleY, rotation * 2);
            p2 = rotate(-scaleX, scaleY, rotation * 2);
        }
        p1.move(static_cast<float>(x), static_cast<float>(y));
        p2.move(static_cast<float>(x), static_cast<float>(y));

        cairo_move_to(cr, x, y);
        cairo_line_to(cr, p1.x, p1.y);
        cairo_line_to(cr, p2.x, p2.y);
        cairo_close_path(cr);
        cairo_fill(cr);

        cairo_destroy(cr);
    }
}
