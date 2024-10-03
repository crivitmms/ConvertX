#include "convertx/convertx.hpp"

#include "catch2/catch_test_macros.hpp"
#include <catch2/catch_template_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

// #include <iostream>
#include <tuple>

using namespace ConvertX;
using namespace Catch::Matchers;

#define TEMP_UNIT_LIST                                                                                                                               \
    Temperatur<TemperaturUnit::CELSIUS>, Temperatur<TemperaturUnit::KELVIN>, Temperatur<TemperaturUnit::FAHRENHEIT>,                                 \
        Temperatur<TemperaturUnit::RANKINE>

TEMPLATE_TEST_CASE("Temp Operations", "[Temperatur][template]", TEMP_UNIT_LIST)
{
    SECTION("Addition")
    {
        TestType unit(10);
        TestType unit2 = 10;
        REQUIRE_THAT((unit + unit2).getvalue(), WithinAbs(20.0, 0.00000001));
        REQUIRE_THAT((unit + 10).getvalue(), WithinAbs(20.0, 0.00000001));
        unit += unit2;
        REQUIRE_THAT(unit.getvalue(), WithinAbs(20.0, 0.00000001));
        unit += 100;
        REQUIRE_THAT(unit.getvalue(), WithinAbs(120.0, 0.00000001));
    }
    SECTION("Subtraction")
    {
        TestType unit(10);
        TestType unit2 = 10;
        REQUIRE_THAT((unit - unit2).getvalue(), WithinAbs(0.0, 0.00000001));
        REQUIRE_THAT((unit - 10).getvalue(), WithinAbs(0.0, 0.00000001));
        unit -= unit;
        REQUIRE_THAT(unit.getvalue(), WithinAbs(0.0, 0.00000001));
        unit -= 100;
        REQUIRE_THAT(unit.getvalue(), WithinAbs(-100.0, 0.00000001));
    }
    SECTION("Multiplication")
    {
        TestType unit(10);
        REQUIRE_THAT((unit * 10).getvalue(), WithinAbs(100.0, 0.00000001));
        unit *= 10;
        REQUIRE_THAT(unit.getvalue(), WithinAbs(100.0, 0.00000001));
        unit *= 0.1;
        REQUIRE_THAT(unit.getvalue(), WithinAbs(10.0, 0.00000001));
    }
    SECTION("Division")
    {
        TestType unit(10);
        REQUIRE_THAT((unit / 10).getvalue(), WithinAbs(1.0, 0.00000001));
        unit /= 10;
        REQUIRE_THAT(unit.getvalue(), WithinAbs(1.0, 0.00000001));
        unit /= 0.1;
        REQUIRE_THAT(unit.getvalue(), WithinAbs(10.0, 0.00000001));
    }
    SECTION("Modulus")
    {
        TestType unit(10);
        unit %= 10;
        REQUIRE_THAT(unit.getvalue(), WithinAbs(0.0, 0.00000001));
        unit = 100;
        REQUIRE_THAT((unit % 9).getvalue(), WithinAbs(1.0, 0.00000001));
    }
    SECTION("throw")
    {
        TestType unit(10);
        REQUIRE_THROWS_WITH(unit.convertTo(static_cast<TemperaturUnit>(-1)), "not a conversion unit");
        REQUIRE_THROWS_WITH(unit.convertToDiff(static_cast<TemperaturUnit>(-1)), "not a conversion unit");
    }
    SECTION("Diff")
    {
        // Temperatur<TemperaturUnit::KELVIN> unit(10);

        TestType unit(10);

        if (typeid(TestType) == typeid(Temperatur<TemperaturUnit::CELSIUS>) || typeid(TestType) == typeid(Temperatur<TemperaturUnit::KELVIN>))
        {
            REQUIRE_THAT(unit.convertToDiff(TemperaturUnit::CELSIUS), WithinAbs(10.0, 0.00000001));
            REQUIRE_THAT(unit.convertToDiff(TemperaturUnit::KELVIN), WithinAbs(10.0, 0.00000001));
            REQUIRE_THAT(unit.convertToDiff(TemperaturUnit::FAHRENHEIT), WithinAbs(18.0, 0.00000001));
            REQUIRE_THAT(unit.convertToDiff(TemperaturUnit::RANKINE), WithinAbs(18.0, 0.00000001));
        }else
        {
            REQUIRE_THAT(unit.convertToDiff(TemperaturUnit::CELSIUS), WithinAbs(5.5555555556, 0.00000001));
            REQUIRE_THAT(unit.convertToDiff(TemperaturUnit::KELVIN), WithinAbs(5.5555555556, 0.00000001));
            REQUIRE_THAT(unit.convertToDiff(TemperaturUnit::FAHRENHEIT), WithinAbs(10.0, 0.00000001));
            REQUIRE_THAT(unit.convertToDiff(TemperaturUnit::RANKINE), WithinAbs(10.0, 0.00000001));
        }
    }
    SECTION("less than"){
        TestType small(10);
        TestType big(100);
        REQUIRE(small < big);
        REQUIRE(not(big < small));
    }
    SECTION("bigger than"){
        TestType small(10);
        TestType big(100);
        REQUIRE(big > small);
        REQUIRE(not(small > big));
    }
}

TEMPLATE_TEST_CASE("Temp convertions", "[Temperatur][template]", TEMP_UNIT_LIST)
{
    auto typelist = std::tuple<TEMP_UNIT_LIST>{};

    /**
     * loops over TEMP_UNIT_LIST with TEMP_UNIT_LIST
     */
    std::apply(
        [&](auto... types)
        {
            ((
                 [&]()
                 {
                     using Type = decltype(types);
                     auto unit = Type(10000);
                     TestType Intermediate = unit;

                     CAPTURE(unit.getUnitType());
                     REQUIRE_THAT(Intermediate.convertTo(unit.getUnitType()), Catch::Matchers::WithinAbs(10000.0, 0.00000001));
                 })(),
             ...);
        },
        typelist);
}
