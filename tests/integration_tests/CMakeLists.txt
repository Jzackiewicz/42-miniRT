cmake_minimum_required(VERSION 3.11)

project(validate_file LANGUAGES CXX C)

# Set debugging flags for compiler
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0 -Wall -Wextra -Werror")

# Enable testing and GoogleTest integration
include(FetchContent)

FetchContent_Declare(
    gtest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.15.2
)

FetchContent_MakeAvailable(gtest)

# Include GoogleTest module
include(GoogleTest)

# # Test executable for validate_extension
# add_executable(validate_file file_validation.cpp 
#     ../../../src/parse/validate_file.c
#     ../../../src/parse/validate_utils.c
#     ../../../src/parse/validate_objects.c
#     ../../../src/parse/validate_settings.c
#     ../../../src/parse/validate_params.c
#     ../../../lib/libft/ft_atoi.c
#     ../../../lib/libft/ft_split.c
#     ../../../lib/libft/ft_2dstr_len.c
#     ../../../lib/libft/ft_atof.c
#     ../../../lib/libft/ft_arr2d_free.c
#     ../../../lib/libft/ft_calloc.c
#     ../../../lib/libft/ft_itoa.c
#     ../../../lib/libft/ft_strlen.c
#     ../../../lib/libft/ft_strncmp.c
#     ../../../lib/libft/ft_bzero.c
#     ../../../lib/libft/check_for_overflow.c
#     ../../../lib/libft/ft_atof.c
#     ../../../lib/libft/ft_isdigit.c
#     ../../../lib/libft/ft_memset.c
#     ../../../lib/libft/gnl/get_next_line.c
#     ../../../lib/libft/gnl/get_next_line_utils.c
#     ../../../lib/libft/ft_strrchr.c)

# # Link GoogleTest
# target_link_libraries(validate_file PRIVATE gtest gtest_main)

# # Set C++ standard version
# target_compile_features(validate_file PRIVATE cxx_std_17)

# # Enable testing
# gtest_discover_tests(validate_file)

# Test executable for validate_extension
add_executable(parse_file parsing_tests.cpp 
    ../../../src/parse/parse.c
    ../../../src/parse/parse_utils.c
    ../../../src/parse/parse_objects.c
    ../../../src/parse/parse_settings.c
    ../../../src/parse/free_objects.c
    ../../../src/parse/validate_file.c
    ../../../src/parse/validate_utils.c
    ../../../src/parse/validate_objects.c
    ../../../src/parse/validate_settings.c
    ../../../src/parse/validate_params.c
    ../../../lib/libft/ft_atoi.c
    ../../../lib/libft/ft_split.c
    ../../../lib/libft/ft_2dstr_len.c
    ../../../lib/libft/ft_atof.c
    ../../../lib/libft/ft_arr2d_free.c
    ../../../lib/libft/ft_calloc.c
    ../../../lib/libft/ft_itoa.c
    ../../../lib/libft/ft_strlen.c
    ../../../lib/libft/ft_strdup.c
    ../../../lib/libft/ft_strncmp.c
    ../../../lib/libft/ft_bzero.c
    ../../../lib/libft/ft_memcpy.c
    ../../../lib/libft/check_for_overflow.c
    ../../../lib/libft/ft_atof.c
    ../../../lib/libft/ft_isdigit.c
    ../../../lib/libft/ft_memset.c
    ../../../lib/libft/gnl/get_next_line.c
    ../../../lib/libft/gnl/get_next_line_utils.c
    ../../../lib/libft/ft_strrchr.c)

# Link GoogleTest
target_link_libraries(parse_file PRIVATE gtest gtest_main)

# Set C++ standard version
target_compile_features(parse_file PRIVATE cxx_std_17)

# Enable testing
gtest_discover_tests(parse_file)

# Add the output path for debugging information
set(CMAKE_BUILD_TYPE Debug)
