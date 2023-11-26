
#ifndef ABSTRACTMUTATOR_HPP
#define ABSTRACTMUTATOR_HPP

#include "common/DataStructures.hpp"
#include "common/Randoms.hpp"

class AbstactMutator {
public:
    virtual ~AbstactMutator() = default;
    virtual void mutate(float& var) = 0;
    virtual void mutate(myData::float2& var) = 0;
    virtual void mutate(myData::float3& var) = 0;
    virtual void mutate(myData::float4& var) = 0;
    virtual void mutate(myData::color_RGBA& var) = 0;
};

#endif // ABSTRACTMUTATOR_HPP
