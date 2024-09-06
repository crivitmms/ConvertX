
test_files = files('length.cpp', 'pressure.cpp', 'temperatur.cpp', 'datasize.cpp')

convertx_test_17 = executable(
    'convertx_test_17',
    test_files,
    dependencies: [catch2_dep, convertx_dep],
    cpp_args : '-std=c++17'
)
convertx_test_20 = executable(
    'convertx_test_20',
    test_files,
    dependencies: [catch2_dep, convertx_dep],
    cpp_args : '-std=c++20'
)
convertx_test_23 = executable(
    'convertx_test_23',
    test_files,
    dependencies: [catch2_dep, convertx_dep],
    cpp_args : '-std=c++23'
)

test('ConvertX tests c++17', convertx_test_17)
test('ConvertX tests c++20', convertx_test_20)
test('ConvertX tests c++23', convertx_test_23)