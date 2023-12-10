#include "Gene.hpp"
#include "common/Randoms.hpp"
#include "genetic/mutators/NormalMutator.hpp"
#include "genetic/mutators/UniformMutator.hpp"
#include <memory>

std::unique_ptr<AbstactMutator> Gene::mutator = std::make_unique<NormalMutator>();

void Gene::randomize()
{
    position = myData::float2(fRand(), fRand());
    rotation = fRand();
    scale = myData::float2(fRand(), fRand());
    color = myData::color_RGBA(fRand(), fRand(), fRand(), fRand());
}
void Gene::mutate(float mutationRate)
{
    mutateColor(mutationRate);
    mutatePos(mutationRate);
    mutateRot(mutationRate);
    mutateSize(mutationRate);
}

void Gene::mutateColor(float mutationRate)
{
    if (fRand() <= mutationRate) {
        Gene::mutator->mutate(color);
    }
}
void Gene::mutatePos(float mutationRate)
{
    if (fRand() <= mutationRate) {
        Gene::mutator->mutate(position);
    }
}
void Gene::mutateRot(float mutationRate)
{
    if (fRand() <= mutationRate) {
        Gene::mutator->mutate(rotation);
    }
}
void Gene::mutateSize(float mutationRate)
{
    if (fRand() <= mutationRate) {
        Gene::mutator->mutate(scale);
    }
}
