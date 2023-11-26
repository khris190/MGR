#include "UniformMutator.hpp"

void UniformMutator::mutate(float& var)
{
    var = distribution(generator);
}

void UniformMutator::mutate(myData::float2& var)
{
    var.x = distribution(generator);
    var.y = distribution(generator);
}

void UniformMutator::mutate(myData::float3& var)
{
    var.x = distribution(generator);
    var.y = distribution(generator);
    var.z = distribution(generator);
}

void UniformMutator::mutate(myData::float4& var)
{
    var.x = distribution(generator);
    var.y = distribution(generator);
    var.z = distribution(generator);
    var.a = distribution(generator);
}

void UniformMutator::mutate(myData::color_RGBA& var)
{
    var.r = distribution(generator);
    var.g = distribution(generator);
    var.b = distribution(generator);
    var.a = distribution(generator);
}
