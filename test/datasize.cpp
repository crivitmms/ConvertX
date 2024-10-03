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

#ifndef NO_LITERALS

TEST_CASE("DataSize User-defined Literals", "[datasize_literals]") {
    auto size_in_bits = 64_bits;
    REQUIRE(size_in_bits.getvalue() == 64.0);

    auto size_in_bytes = 1024_bytes;
    REQUIRE(size_in_bytes.getvalue() == 1024.0);

    auto size_in_kib = 1.5_kib;
    REQUIRE(size_in_kib.getvalue() == 1.5);

    auto size_in_mib = 2_mib;
    REQUIRE(size_in_mib.getvalue() == 2.0);

    auto size_in_gib = 64_gib;
    REQUIRE(size_in_gib.getvalue() == 64.0);

    auto size_in_tib = 1.25_tib;
    REQUIRE(size_in_tib.getvalue() == 1.25);

    auto size_in_pib = 0.5_pib;
    REQUIRE(size_in_pib.getvalue() == 0.5);

    auto size_in_eib = 100_eib;
    REQUIRE(size_in_eib.getvalue() == 100.0);

    auto size_in_zib = 10_zib;
    REQUIRE(size_in_zib.getvalue() == 10.0);

    auto size_in_yib = 5_yib;
    REQUIRE(size_in_yib.getvalue() == 5.0);
}

#endif

TEMPLATE_TEST_CASE("DataSize Operations", "[DataSize][template]", DATA_UNIT_LIST)
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
        REQUIRE_THROWS_WITH(unit.convertTo(static_cast<DataUnit>(-1)), "not a conversion unit");
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
