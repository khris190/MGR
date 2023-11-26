#ifndef NORMALMUTATOR_HPP
#define NORMALMUTATOR_HPP

#include "AbstractMutator.hpp"
#include "common/Randoms.hpp"
#include <random>

class NormalMutator : public AbstactMutator {
    std::default_random_engine generator;
    std::normal_distribution<float> distribution = std::normal_distribution<float>(0.0, 0.1);

public:
    NormalMutator() = default;
    ~NormalMutator() override = default;
    void mutate(float& var) override;
    void mutate(myData::float2& var) override;
    void mutate(myData::float3& var) override;
    void mutate(myData::float4& var) override;
    void mutate(myData::color_RGBA& var) override;

private:
    void cutoff(float& var, float min = 0, float max = 1.0) const;
};

#endif // NORMALMUTATOR_HPP
