#ifndef UNIFORMMUTATOR_HPP
#define UNIFORMMUTATOR_HPP

#include "genetic/mutators/AbstractBasicMutator.hpp"
#include <random>

class UniformMutator : public AbstactBasicMutator {
private:
    std::default_random_engine generator;
    std::uniform_real_distribution<float> distribution = std::uniform_real_distribution<float>(0.0, 1.0);

public:
    using AbstactBasicMutator::mutate;
    UniformMutator() = default;
    ~UniformMutator() override = default;
    void mutate(float& var) override;
};

#endif // UNIFORMMUTATOR_HPP
