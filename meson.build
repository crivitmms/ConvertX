project(
    'ConvertX',
    'cpp',
    default_options: [
        'warning_level=3',
        'werror=true',
        'default_library=static',
    ],
)

src_files = []
header_only = []
cpp_args = []

if get_option('remove_literals')
    cpp_args += '-DNO_LITERALS=1'
    add_project_arguments(cpp_args, language: 'cpp')
endif

convertx_inc = include_directories('src', is_system: true)
convertx_dep = declare_dependency(
    include_directories: convertx_inc,
    compile_args: cpp_args,
)

if get_option('build_test_targets')

    catch2_proj = subproject('catch2', default_options: ['warning_level=0', 'werror=false'])
    catch2_dep = catch2_proj.get_variable('catch2_with_main_dep')

    subdir('test')

endif