#ifndef ABSTRACTBASICMUTATOR_HPP
#define ABSTRACTBASICMUTATOR_HPP
#include "AbstractMutator.hpp"

class AbstactBasicMutator : public AbstactMutator {
public:
    using AbstactMutator::mutate;
    ~AbstactBasicMutator() override = default;
    void mutate(myData::float2& var) final;
    void mutate(myData::float3& var) final;
    void mutate(myData::float4& var) final;
    void mutate(myData::color_RGBA& var) final;
};

#endif // ABSTRACTBASICMUTATOR_HPP
