#include "genetic/mutators/NormalMutator.hpp"
#include "genetic/mutators/UniformMutator.hpp"
#include <gtest/gtest.h>

// Demonstrate some basic assertions.
TEST(HelloTest, BasicAssertions)
{
    // Expect two strings not to be equal.
    EXPECT_STRNE("hello", "world");
    // Expect equality.
    EXPECT_EQ(7 * 6, 42);
}
TEST(NORMALTEST, tooManyCutoffs)
{
    const int bucketAmount = 100;
    int buckets[bucketAmount];
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
    int buckets[bucketAmount];
    for (size_t i = 0; i < bucketAmount; i++) {
        buckets[i] = 0;
    }
    UniformMutator mutator;
    float testVar = 0.5;
    const size_t iter = 100000;
    for (size_t i = 0; i < iter; i++) {
        mutator.mutate(testVar);
        buckets[(int)std::round(testVar * (bucketAmount - 1))]++;
    }
    for (size_t i = 0; i < bucketAmount; i++) {
        std::cout << i << ":" << buckets[i] << std::endl;
    }
    for (size_t i = 0; i < bucketAmount; i++) {
        std::cout << i << ":" << buckets[i] / (iter / bucketAmount) << std::endl;
        if (i == 0) {
            EXPECT_TRUE(std::round(buckets[i] / (iter / bucketAmount)) == std::round(buckets[bucketAmount - 1] / (iter / bucketAmount)));
        } else if (i < bucketAmount - 2) {
            EXPECT_TRUE(std::round(buckets[i] / (iter / bucketAmount)) == std::round(buckets[i + 1] / (iter / bucketAmount)));
        }
    }
}
