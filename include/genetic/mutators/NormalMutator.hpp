#ifndef NORMALMUTATOR_HPP
#define NORMALMUTATOR_HPP

#include "genetic/mutators/AbstractBasicMutator.hpp"
#include <random>

class NormalMutator : public AbstactBasicMutator {
    std::mt19937 generator;
    std::normal_distribution<float> distribution = std::normal_distribution<float>(0.0f, 0.1f);

public:
    using AbstactBasicMutator::mutate;
    NormalMutator() = default;
    ~NormalMutator() override = default;
    void mutate(float& var) override;

private:
    void cutoff(float& var, float min = 0, float max = 1.0) const;
};

#endif // NORMALMUTATOR_HPP
