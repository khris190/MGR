#include "AbstractBasicMutator.hpp"

void AbstactBasicMutator::mutate(myData::float2& var)
{
    mutate(var.x);
    mutate(var.y);
}

void AbstactBasicMutator::mutate(myData::float3& var)
{
    mutate(var.x);
    mutate(var.y);
    mutate(var.z);
}

void AbstactBasicMutator::mutate(myData::float4& var)
{
    mutate(var.x);
    mutate(var.y);
    mutate(var.z);
    mutate(var.a);
}

void AbstactBasicMutator::mutate(myData::color_RGBA& var)
{
    mutate(var.r);
    mutate(var.g);
    mutate(var.b);
    mutate(var.a);
}
