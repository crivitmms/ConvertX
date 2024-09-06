#include "convertx/convertx.hpp"

#include "catch2/catch_test_macros.hpp"
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include <catch2/catch_template_test_macros.hpp>

#include <tuple>

using namespace ConvertX;
using namespace Catch::Matchers;

#define DATA_UNIT_LIST \
    DataSize<DataUnit::BITS>,       \
    DataSize<DataUnit::NIBBLE>,     \
    DataSize<DataUnit::BYTES>,      \
    DataSize<DataUnit::KILOBYTES>,  \
    DataSize<DataUnit::MEGABYTES>,  \
    DataSize<DataUnit::GIGABYTES>,  \
    DataSize<DataUnit::TERABYTES>,  \
    DataSize<DataUnit::PETABYTES>,  \
    DataSize<DataUnit::EXABYTES>,   \
    DataSize<DataUnit::ZETTABYTES>, \
    DataSize<DataUnit::YOTTABYTES>

TEMPLATE_TEST_CASE("DataSize Operations", "[DataSize][template]", DATA_UNIT_LIST)
{
    SECTION("Addition"){
        TestType unit(10);
        unit += unit;
        REQUIRE_THAT(unit.getvalue(), WithinAbs(20.0, 0.00000001));
        unit += 100;
        REQUIRE_THAT(unit.getvalue(), WithinAbs(120.0, 0.00000001));
    }
    SECTION("Subtraction"){
        TestType unit(10);
        unit -= unit;
        REQUIRE_THAT(unit.getvalue(), WithinAbs(0.0, 0.00000001));
        unit -= 100;
        REQUIRE_THAT(unit.getvalue(), WithinAbs(-100.0, 0.00000001));
    }
    SECTION("Multiplication"){
        TestType unit(10);
        unit *= 10;
        REQUIRE_THAT(unit.getvalue(), WithinAbs(100.0, 0.00000001));
        unit *= 0.1;
        REQUIRE_THAT(unit.getvalue(), WithinAbs(10.0, 0.00000001));
    }
    SECTION("Division"){
        TestType unit(10);
        unit /= 10;
        REQUIRE_THAT(unit.getvalue(), WithinAbs(1.0, 0.00000001));
        unit /= 0.1;
        REQUIRE_THAT(unit.getvalue(), WithinAbs(10.0, 0.00000001));
    }
    SECTION("Modulus"){
        TestType unit(10);
        unit %= 10;
        REQUIRE_THAT(unit.getvalue(), WithinAbs(0.0, 0.00000001));
        unit = 100;
        REQUIRE_THAT((unit % 9).getvalue(), WithinAbs(1.0, 0.00000001));
    }
}

TEMPLATE_TEST_CASE("DataSize convertions", "[DataSize][template]", DATA_UNIT_LIST)
{
    auto typelist = std::tuple<DATA_UNIT_LIST>{};

    /**
     * loops over DATA_UNIT_LIST with DATA_UNIT_LIST
     */
    std::apply([&](auto... types) {
        (([&]() {
            using Type = decltype(types);
            auto unit = Type(100);
            TestType Intermediate = unit;

            CAPTURE(unit.getUnitType());
            REQUIRE_THAT(Intermediate.convertTo(unit.getUnitType()), 
                         Catch::Matchers::WithinAbs(100.0, 0.00000001));
        })(), ...);
    }, typelist);
}
