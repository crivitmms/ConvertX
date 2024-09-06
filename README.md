# ConvertX

**ConvertX** is a C++ library designed to facilitate seamless unit conversions between different types. Whether you need to convert lengths, temperaturs, or pressures, ConvertX handles the complexity for you. Additionally, it supports mathematical operations on these units, ensuring that conversions remain accurate and consistent throughout your calculations.

This library was born out of a practical need in my professional work, where unit conversions are essential. Moreover, it served as an opportunity to experience the process of creating and releasing an open-source library, providing valuable insight into software development and distribution.

## Features

- **Automatic Conversion**: Convert units effortlessly with automatic conversion between supported types.
- **Mathematical Operations**: Perform math operations on different units, ensuring consistent and accurate conversions.
- **`constexpr` Support**: Leverage `constexpr` to perform conversions at compile time, enhancing performance and reliability.

## Installation / Include

ConvertX uses the Meson build system. To include ConvertX in your project, add it as a dependency:

### `subprojects/convertx.wrap`
```meson
[wrap-git]
directory = convertx
url = git@github.com:crivitmms/ConvertX.git
revision = V1.0
depth = 1
```
### `meson.build`
```meson
convertx = subproject('convertx')
convertx_dep = convertx.get_variable('convertx_dep')
```
## Small Example
```C++
#include "convertx/convertx.hpp"
#include "iostream"
using namespace ConvertX;
// Function that returns a Length<LengthUnit::CENTIMETER> based on the input argument
Length<LengthUnit::CENTIMETER> get5(int args)
{
    if( args % 2 == 0){
        return Length<LengthUnit::FEET>(5); // Converts 5 feet to centimeters
    }
    else{
        return Length<LengthUnit::NAUTICALMILES>(5); // Converts 5 nautical miles to centimeters
    }
}
// Function to print the length in meters
void printmeter(const Length<LengthUnit::METER> &meters)
{
    std::cout << meters.getvalue() << " meters" << std::endl;
}
// Lambda function to add 5 feet to a length
auto add5feet = [](auto &unit)
{
    unit += Length<LengthUnit::FEET>(5);
};

int main(int args, char **)
{
    Length<LengthUnit::ASTRONOMICALUNIT> asto = get5(args);
    add5feet(asto);
    printmeter(asto);
    return 0;
}
```

## Limits

ConvertX requires that all units be known at compile time.<br>
This design ensures that conversions and calculations are optimized and validated during compilation, making use of constexpr wherever possible.<br> 
For scenarios where units need to be determined at runtime, consider using tools like `std::variant` and `std::visit` to handle the logic dynamically.

## Currently supported units
### [Supported units list](README_UNITS.md)

## Options

- **`build_test_targets`**:  
  *Default*: `false`  
  When set to `true`, this enables building of the test targets, allowing unit tests to be compiled and run.

- **`remove_literals`**:  
  *Default*: `false`  
  When set to `true`, this disables the use of user-defined literals (e.g., `_gib`, `_mib`) for easily creating `DataSize<DataUnit::Unit>` instances.

## Dependencies

ConvertX itself has no external dependencies.<br>
However, the unit tests utilize the [Catch2](https://github.com/catchorg/Catch2) testing framework.

To include and run the unit tests in your project, ensure that the `build_test_targets` option is enabled in your Meson configuration:
```meson
convertx = subproject('convertx', default_options: ['build_test_targets=true'])
```
The project provides three test executables, each targeting a different C++ standard version: C++17, C++20, and C++23.

## Licenses
**ConvertX:** Boost Software License - Version 1.0 - August 17th, 2003<br>
**Catch2:** `subprojects/Catch2-*/LICENSE.txt`

## Contributing
Contributions are welcome!<br>
Please fork the repository and submit a pull request for any enhancements or bug fixes.