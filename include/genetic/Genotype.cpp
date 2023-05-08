#include "Genotype.hpp"

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

Genotype::~Genotype()
{
    logger.LogDeb("Free genotype");
    if (gene_arr) {
        free(gene_arr);
    }
}
