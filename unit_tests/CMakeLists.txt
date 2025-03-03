cmake_minimum_required(VERSION 3.11)

project(tokenizer_tests LANGUAGES CXX C)

include(FetchContent)

FetchContent_Declare(
    gtest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.15.2
)

FetchContent_MakeAvailable(gtest)

# Define test executable validate_file
add_executable(validate_file validate_file.cpp 
    ../../src/parse/validate_file.c
    ../../lib/libft/ft_strlen.c
    ../../lib/libft/ft_strncmp.c)

target_link_libraries(validate_file PRIVATE gtest gtest_main)
target_compile_features(validate_file PRIVATE cxx_std_17)

# Discover and add tests for validate_file
include(GoogleTest)
gtest_discover_tests(validate_file)
