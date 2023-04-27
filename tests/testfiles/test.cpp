#ifndef SOME_UNIQUE_NAME_HERE1
#define SOME_UNIQUE_NAME_HERE1
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../doctest.h"

TEST_CASE(("test") * doctest::test_suite("fisrt"))
{
    REQUIRE(10 == 10);
}
TEST_CASE(("test2") * doctest::test_suite("fisrt"))
{
    REQUIRE(11 == 11);
}
#endif