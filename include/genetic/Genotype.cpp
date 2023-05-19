#include "Genotype.hpp"
#include <cstddef>

int Genotype::getSize() { return genes.size(); }

Genotype::Genotype(int size_)
{
    this->genes.reserve(size_);
    for (size_t i = 0; i < size_; i++) {
        this->genes.push_back(Gene());
        this->genes[i].Randomize();
    }
}

// randomly swap all shapes order
void Genotype::SwapAll(float mutation_rate)
{
    for (size_t i = 0; i < genes.size(); i++) {
        this->SwapOne(mutation_rate, i);
    }
}

// randomly swap one shapes order
void Genotype::SwapOne(float mutation_rate, int i)
{
    if (i < 0) {
        i = rand() % genes.size();
    }
    if (fRand() <= mutation_rate * 0) {
        int swap = rand() % genes.size() - 1;
        if (swap >= i) {
            swap += 1;
        }

        Gene tmp = genes[i];
        genes[i] = genes[swap];
        genes[swap] = tmp;
    }
}

void Genotype::Mutate(float mutation_rate)
{
    for (size_t i = 0; i < genes.size(); i++) {
        genes[i].Mutate(mutation_rate);
    }
    // TODO seems to not work on linux 6.1 nor on 6.0 ?
    // SwapOne(mutation_rate);
}
void Genotype::Wiggle(float mutation_rate)
{
    for (size_t i = 0; i < genes.size(); i++) {
        genes[i].Wiggle(mutation_rate);
    }
}

void Genotype::Cross(Genotype& parent1_, Genotype& parent2_)
{
    if (parent1_.genes.size() != parent2_.genes.size()) {
        throw "parents size mismatch";
    }
    for (size_t i = 0; i < parent1_.genes.size(); i++) {
        if (rand() % 2) {
            this->genes[i] = parent1_.genes[i];
        } else {
            this->genes[i] = parent2_.genes[i];
        }
    }
}

//???
inline myData::position rotate(float x, float y, float angle)
{
    return myData::position(x * cos(angle) - y * sin(angle), x * sin(angle) + y * cos(angle));
}

// TODO use opengl
void Genotype::Draw(cairo_surface_t* img, float Scale)
{
    cairo_t* cr;
    for (size_t i = 0; i < genes.size(); i++) {
        int _width, _height;

        _width = cairo_image_surface_get_width(img);
        _height = cairo_image_surface_get_height(img);

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wnarrowing"

        float color[4] = { genes[i].color.r, genes[i].color.g, genes[i].color.b, genes[i].color.a };

#pragma GCC diagnostic pop

        int x = genes[i].position.x * _width;
        int y = genes[i].position.y * _height;

        float scaleX = genes[i].scale.x * _width * Scale;
        float scaleY = genes[i].scale.y * _height * Scale;
        float rotation = genes[i].rotation * 3.14;

        // kwadrat
        if (genes[i].type_of_shape == myData::rectangle) {
            cr = cairo_create(img);
            cairo_set_source_rgba(cr, color[0], color[1], color[2], color[3]);
            myData::position p1, p2, p3, p4;
            if (rotation != 0) {
                p1 = rotate(scaleX, scaleY, rotation);
                p2 = rotate(-scaleX, scaleY, rotation);
                p3 = rotate(scaleX, -scaleY, rotation);
                p4 = rotate(-scaleX, -scaleY, rotation);
            }
            p1.move(x, y);
            p2.move(x, y);
            p3.move(x, y);
            p4.move(x, y);

            cairo_move_to(cr, p1.x, p1.y);
            cairo_line_to(cr, p2.x, p2.y);
            cairo_line_to(cr, p4.x, p4.y);
            cairo_line_to(cr, p3.x, p3.y);
            cairo_close_path(cr);
            cairo_fill(cr);
        } else if (genes[i].type_of_shape == myData::ellipse) {
            cr = cairo_create(img);
            cairo_set_source_rgba(cr, color[0], color[1], color[2], color[3]);
            cairo_translate(cr, x, y);
            cairo_rotate(cr, rotation * 3.14);
            cairo_scale(cr, scaleX, scaleY);
            cairo_arc(cr, 0, 0, 1, 0, 2 * 3.14);
            cairo_fill(cr);
        } else if (genes[i].type_of_shape == myData::triangle) {
            cr = cairo_create(img);
            cairo_set_source_rgba(cr, color[0], color[1], color[2], color[3]);
            myData::position p1, p2;
            if (rotation != 0) {
                p1 = rotate(scaleX, scaleY, rotation * 2);
                p2 = rotate(-scaleX, scaleY, rotation * 2);
            }
            p1.move(x, y);
            p2.move(x, y);

            cairo_move_to(cr, x, y);
            cairo_line_to(cr, p1.x, p1.y);
            cairo_line_to(cr, p2.x, p2.y);
            cairo_close_path(cr);
            cairo_fill(cr);
        }

        cairo_destroy(cr);
    }
}

Genotype::~Genotype() { }
