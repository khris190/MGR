#include "NormalMutator.hpp"
void NormalMutator::mutate(float& var)
{
    var += distribution(generator);
    cutoff(var);
}

void NormalMutator::cutoff(float& var, float min, float max) const
{
    if (var < min) {
        var = min;
    } else if (var > max) {
        var = max;
    }
}
