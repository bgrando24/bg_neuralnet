#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

int add(int a, int b)
{
    return a + b;
}

TEST_CASE("testing add function")
{
    CHECK(add(2, 2) == 4);
}