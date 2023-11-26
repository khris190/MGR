#include "genetic/mutators/NormalMutator.hpp"
#include "genetic/mutators/UniformMutator.hpp"
#include <gtest/gtest.h>

TEST(NORMALTEST, tooManyCutoffs)
{
    const int bucketAmount = 100;
    std::array<int, bucketAmount> buckets;
    for (size_t i = 0; i < bucketAmount; i++) {
        buckets[i] = 0;
    }
    NormalMutator mutator;
    float testVar;
    const size_t iter = 100000;
    for (size_t i = 0; i < iter; i++) {
        testVar = 0.5;
        mutator.mutate(testVar);
        buckets[(int)std::round(testVar * (bucketAmount - 1))]++;
    }
    for (size_t i = 0; i < bucketAmount; i++) {
        std::cout << i << ":" << buckets[i] << std::endl;
        if (i < bucketAmount / 2) {
            EXPECT_TRUE(buckets[i] <= 1.2 * buckets[i + 1] + 5);
        } else {
            EXPECT_TRUE(buckets[i] <= 1.2 * buckets[i - 1] + 5);
        }
    }
}
TEST(UNIFORMTEST, distribution)
{
    const int bucketAmount = 10;
    const int expected = 10000;
    std::array<int, bucketAmount> buckets;
    for (size_t i = 0; i < bucketAmount; i++) {
        buckets[i] = 0;
    }
    UniformMutator mutator;
    float testVar = 0.5;
    const size_t iter = expected * bucketAmount;
    for (size_t i = 0; i < iter; i++) {
        mutator.mutate(testVar);
        buckets[(int)std::round(testVar * bucketAmount - 0.5)]++;
    }
    for (size_t i = 0; i < bucketAmount; i++) {
        std::cout << i << ":" << buckets[i] << std::endl;
    }
    for (size_t i = 0; i < bucketAmount; i++) {
        std::cout << i << ":" << buckets[i] / expected << std::endl;
        if (i < bucketAmount - 1) {
            EXPECT_TRUE(std::round((float)buckets[i] / expected) == std::round((float)buckets[i + 1] / expected));
        }
    }
}
