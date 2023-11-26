#include "NormalMutator.hpp"
void NormalMutator::mutate(float& var)
{
    var += distribution(generator);
    cutoff(var);
}

void NormalMutator::mutate(myData::float2& var)
{
    var.x += distribution(generator);
    cutoff(var.x);
    var.y += distribution(generator);
    cutoff(var.y);
}

void NormalMutator::mutate(myData::float3& var)
{
    var.x += distribution(generator);
    cutoff(var.x);
    var.y += distribution(generator);
    cutoff(var.y);
    var.z += distribution(generator);
    cutoff(var.z);
}

void NormalMutator::mutate(myData::float4& var)
{
    var.x += distribution(generator);
    cutoff(var.x);
    var.y += distribution(generator);
    cutoff(var.y);
    var.z += distribution(generator);
    cutoff(var.z);
    var.a += distribution(generator);
    cutoff(var.a);
}

void NormalMutator::mutate(myData::color_RGBA& var)
{
    var.r += distribution(generator);
    cutoff(var.r);
    var.g += distribution(generator);
    cutoff(var.g);
    var.b += distribution(generator);
    cutoff(var.b);
    var.a += distribution(generator);
    cutoff(var.a);
}

void NormalMutator::cutoff(float& var, float min, float max) const
{
    if (var < min) {
        var = min;
    } else if (var > max) {
        var = max;
    }
}
