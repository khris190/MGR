#include "Genotype.hpp"
#include "common/DataStructures.hpp"

Genotype::Genotype(int size_)
{
    size = size_;
    gene_arr = (Gene*)malloc(sizeof(Gene) * size_);
    for (size_t i = 0; i < size_; i++) {
        gene_arr[i].CreateRandom();
    }
}

// randomly swap all shapes order
void Genotype::SwapAll(float mutation_rate)
{
    for (size_t i = 0; i < size; i++) {
        this->SwapOne(mutation_rate, i);
    }
}

// randomly swap one shapes order
void Genotype::SwapOne(float mutation_rate, int i)
{
    if (i < 0) {
        i = rand() % size;
    }
    if (fRand() <= mutation_rate * 0) {
        int swap = rand() % size - 1;
        if (swap >= i) {
            swap += 1;
        }

        Gene tmp = gene_arr[i];
        gene_arr[i] = gene_arr[swap];
        gene_arr[swap] = tmp;
    }
}

void Genotype::Mutate(float mutation_rate)
{
    for (size_t i = 0; i < size; i++) {
        gene_arr[i].Mutate(mutation_rate);
    }
    // TODO seems to not work on linux 6.1 nor on 6.0 ?
    // SwapOne(mutation_rate);
}
void Genotype::Wiggle(float mutation_rate)
{
    for (size_t i = 0; i < size; i++) {
        gene_arr[i].Wiggle(mutation_rate);
    }
}

void Genotype::Cross(Genotype* parent1_, Genotype* parent2_)
{
    if (parent1_->size != parent2_->size) {
        throw "parents size mismatch";
    }
    for (size_t i = 0; i < parent1_->size; i++) {
        if (rand() % 2) {
            this->gene_arr[i] = parent1_->gene_arr[i];
        } else {
            this->gene_arr[i] = parent2_->gene_arr[i];
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
    for (size_t i = 0; i < size; i++) {
        int _width, _height;

        _width = cairo_image_surface_get_width(img);
        _height = cairo_image_surface_get_height(img);

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wnarrowing"

        float color[4] = { gene_arr[i].color.r, gene_arr[i].color.g, gene_arr[i].color.b, gene_arr[i].color.a };

#pragma GCC diagnostic pop

        int x = gene_arr[i].position.x * _width;
        int y = gene_arr[i].position.y * _height;

        float scaleX = gene_arr[i].scale.x * _width * Scale * 0.5;
        float scaleY = gene_arr[i].scale.y * _height * Scale * 0.5;
        float rotation = gene_arr[i].rotation * 3.14;

        // kwadrat
        if (gene_arr[i].type_of_shape == myData::rectangle) {
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
        } else if (gene_arr[i].type_of_shape == myData::ellipse) {
            cr = cairo_create(img);
            cairo_set_source_rgba(cr, color[0], color[1], color[2], color[3]);
            cairo_translate(cr, x, y);
            cairo_rotate(cr, rotation * 3.14);
            cairo_scale(cr, scaleX, scaleY);
            cairo_arc(cr, 0, 0, 1, 0, 2 * 3.14);
            cairo_fill(cr);
        } else if (gene_arr[i].type_of_shape == myData::triangle) {
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

Genotype::~Genotype()
{
    logger.LogDeb("Free genotype");
    if (gene_arr) {
        free(gene_arr);
    }
}
