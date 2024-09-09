#include "convertx/convertx.hpp"

#include "catch2/catch_test_macros.hpp"
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include <catch2/catch_template_test_macros.hpp>

// #include <iostream>
#include <tuple>

using namespace ConvertX;
using namespace Catch::Matchers;


#define PRESSURE_UNIT_LIST \
    Pressure<PressureUnit::PA>,         \
    Pressure<PressureUnit::KPA>,        \
    Pressure<PressureUnit::BAR>,        \
    Pressure<PressureUnit::PSI>,        \
    Pressure<PressureUnit::ATMOSPHERE>

TEMPLATE_TEST_CASE("Pressure Operations", "[Pressure][template]", PRESSURE_UNIT_LIST)
{
    SECTION("Addition"){
        TestType unit(10);
        TestType unit2 = 10;
        REQUIRE_THAT((unit+unit2).getvalue(), WithinAbs(20.0, 0.00000001));
        REQUIRE_THAT((unit+10).getvalue(), WithinAbs(20.0, 0.00000001));
        unit += unit2;
        REQUIRE_THAT(unit.getvalue(), WithinAbs(20.0, 0.00000001));
        unit += 100;
        REQUIRE_THAT(unit.getvalue(), WithinAbs(120.0, 0.00000001));
    }
    SECTION("Subtraction"){
        TestType unit(10);
        TestType unit2 = 10;
        REQUIRE_THAT((unit-unit2).getvalue(), WithinAbs(0.0, 0.00000001));
        REQUIRE_THAT((unit-10).getvalue(), WithinAbs(0.0, 0.00000001));
        unit -= unit;
        REQUIRE_THAT(unit.getvalue(), WithinAbs(0.0, 0.00000001));
        unit -= 100;
        REQUIRE_THAT(unit.getvalue(), WithinAbs(-100.0, 0.00000001));
    }
    SECTION("Multiplication"){
        TestType unit(10);
        REQUIRE_THAT((unit*10).getvalue(), WithinAbs(100.0, 0.00000001));
        unit *= 10;
        REQUIRE_THAT(unit.getvalue(), WithinAbs(100.0, 0.00000001));
        unit *= 0.1;
        REQUIRE_THAT(unit.getvalue(), WithinAbs(10.0, 0.00000001));
    }
    SECTION("Division"){
        TestType unit(10);
        REQUIRE_THAT((unit/10).getvalue(), WithinAbs(1.0, 0.00000001));
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
    SECTION("throw"){
        TestType unit(10);
        REQUIRE_THROWS_WITH(unit.convertTo(static_cast<PressureUnit>(-1)), "not a conversion unit");
    }
}

TEMPLATE_TEST_CASE("Pressure convertions", "[Pressure][template]", PRESSURE_UNIT_LIST)
{
    auto typelist = std::tuple<PRESSURE_UNIT_LIST>{};

    /**
     * loops over TEMP_UNIT_LIST with TEMP_UNIT_LIST
     */
    std::apply([&](auto... types) {
        (([&]() {
            using Type = decltype(types);
            auto unit = Type(10000);
            TestType Intermediate = unit;

            CAPTURE(unit.getUnitType());
            REQUIRE_THAT(Intermediate.convertTo(unit.getUnitType()), 
                         Catch::Matchers::WithinAbs(10000.0, 0.00000001));
        })(), ...);
    }, typelist);
}
