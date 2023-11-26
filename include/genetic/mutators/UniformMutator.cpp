#include "UniformMutator.hpp"

void UniformMutator::mutate(float& var)
{
    var = distribution(generator);
}
