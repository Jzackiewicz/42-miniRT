cmake_minimum_required(VERSION 3.11)

project(validate_file LANGUAGES CXX C)

set(CMAKE_CXX_FLAGS_DEBUG "-g -O0 -Wall -Wextra -Werror")

include(FetchContent)

FetchContent_Declare(
    gtest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.15.2
)

FetchContent_MakeAvailable(gtest)

add_executable(validate_extension validate_extension.cpp 
    ../../src/parse/validate_file.c
    ../../lib/libft/ft_strlen.c
    ../../lib/libft/ft_strncmp.c)

target_link_libraries(validate_extension PRIVATE gtest gtest_main)
target_compile_features(validate_extension PRIVATE cxx_std_17)

include(GoogleTest)
gtest_discover_tests(validate_extension)

add_executable(validate_colors validate_colors.cpp 
    ../../src/parse/validate_utils.c
    ../../lib/libft/ft_atoi.c
    ../../lib/libft/ft_split.c
    ../../lib/libft/ft_2dstr_len.c
    ../../lib/libft/check_for_overflow.c
    ../../lib/libft/ft_arr2d_free.c
    ../../lib/libft/ft_calloc.c
    ../../lib/libft/ft_itoa.c
    ../../lib/libft/ft_strncmp.c
    ../../lib/libft/ft_bzero.c
    ../../lib/libft/ft_strlen.c
    )

target_link_libraries(validate_colors PRIVATE gtest gtest_main)
target_compile_features(validate_colors PRIVATE cxx_std_17)

gtest_discover_tests(validate_colors)
