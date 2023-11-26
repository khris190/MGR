#ifndef UNIFORMMUTATOR_HPP
#define UNIFORMMUTATOR_HPP

#include "AbstractMutator.hpp"
#include "common/Randoms.hpp"
#include <random>

class UniformMutator : public AbstactMutator {
private:
    std::default_random_engine generator;
    std::uniform_real_distribution<float> distribution = std::uniform_real_distribution<float>(0.0, 1.0);

public:
    UniformMutator() = default;
    ~UniformMutator() override = default;
    void mutate(float& var) override;
    void mutate(myData::float2& var) override;
    void mutate(myData::float3& var) override;
    void mutate(myData::float4& var) override;
    void mutate(myData::color_RGBA& var) override;
};

#endif // UNIFORMMUTATOR_HPP
