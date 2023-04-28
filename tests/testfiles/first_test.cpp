#ifndef SOME_UNIQUE_NAME_HERE
#define SOME_UNIQUE_NAME_HERE

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../doctest.h"

TEST_CASE(("test") * doctest::test_suite("fisrt copy"))
{
    REQUIRE(10 == 10);
}
TEST_CASE(("test2") * doctest::test_suite("fisrt copy"))
{
    REQUIRE(11 != 11);
}

#endif
