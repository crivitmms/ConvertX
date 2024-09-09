#include "convertx/constexprMath.hpp"

#include "catch2/catch_test_macros.hpp"
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include <catch2/catch_template_test_macros.hpp>

using namespace ConvertX;
using namespace Catch::Matchers;

TEST_CASE("power 0")
{
    REQUIRE_THAT(Math::constexpr_pow(10,0), WithinAbs(1.0, 0.00000001));
}