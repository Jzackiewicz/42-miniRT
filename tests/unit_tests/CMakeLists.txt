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

# Include GoogleTest module
include(GoogleTest)

# # Test executable for validate_extension
# add_executable(validate_extension validate_extension.cpp 
#     ../../src/parse/validate_file.c
#     ../../lib/libft/ft_strlen.c
#     ../../lib/libft/ft_strncmp.c)

# target_link_libraries(validate_extension PRIVATE gtest gtest_main)
# target_compile_features(validate_extension PRIVATE cxx_std_17)
# gtest_discover_tests(validate_extension)

# # Test executable for validate_colors
# # add_executable(validate_colors validate_colors.cpp 
# #     ../../src/parse/validate_utils.c
# #     ../../lib/libft/ft_atoi.c
# #     ../../lib/libft/ft_split.c
# #     ../../lib/libft/ft_2dstr_len.c
# #     ../../lib/libft/check_for_overflow.c
# #     ../../lib/libft/ft_arr2d_free.c
# #     ../../lib/libft/ft_calloc.c
# #     ../../lib/libft/ft_itoa.c
# #     ../../lib/libft/ft_strncmp.c
# #     ../../lib/libft/ft_bzero.c
# #     ../../lib/libft/ft_strlen.c
# #     ../../lib/libft/ft_atof.c
# #     ../../lib/libft/ft_isdigit.c)

# # target_link_libraries(validate_colors PRIVATE gtest gtest_main)
# # target_compile_features(validate_colors PRIVATE cxx_std_17)
# # gtest_discover_tests(validate_colors)

# # Test executable for validate_ambient
# # add_executable(validate_ambient validate_ambient.cpp 
# #     ../../src/parse/validate_settings.c
# #     ../../src/parse/validate_utils.c
# #     ../../lib/libft/ft_atoi.c
# #     ../../lib/libft/ft_split.c
# #     ../../lib/libft/ft_2dstr_len.c
# #     ../../lib/libft/ft_atof.c
# #     ../../lib/libft/ft_arr2d_free.c
# #     ../../lib/libft/ft_calloc.c
# #     ../../lib/libft/ft_itoa.c
# #     ../../lib/libft/ft_strncmp.c
# #     ../../lib/libft/ft_bzero.c
# #     ../../lib/libft/ft_strlen.c
# #     ../../lib/libft/check_for_overflow.c)

# # target_link_libraries(validate_ambient PRIVATE gtest gtest_main)
# # target_compile_features(validate_ambient PRIVATE cxx_std_17)
# # gtest_discover_tests(validate_ambient)

# add_executable(check_coords check_coords.cpp 
#     ../../src/parse/validate_settings.c
#     ../../src/parse/validate_utils.c
#     ../../lib/libft/ft_atoi.c
#     ../../lib/libft/ft_split.c
#     ../../lib/libft/ft_2dstr_len.c
#     ../../lib/libft/ft_atof.c
#     ../../lib/libft/ft_arr2d_free.c
#     ../../lib/libft/ft_calloc.c
#     ../../lib/libft/ft_itoa.c
#     ../../lib/libft/ft_strncmp.c
#     ../../lib/libft/ft_bzero.c
#     ../../lib/libft/ft_strlen.c
#     ../../lib/libft/check_for_overflow.c
#     ../../lib/libft/ft_atof.c
#     ../../lib/libft/ft_isdigit.c)

# target_link_libraries(check_coords PRIVATE gtest gtest_main)
# target_compile_features(check_coords PRIVATE cxx_std_17)
# gtest_discover_tests(check_coords)

# add_executable(check_vector check_vector.cpp 
#     ../../src/parse/validate_settings.c
#     ../../src/parse/validate_utils.c
#     ../../lib/libft/ft_atoi.c
#     ../../lib/libft/ft_split.c
#     ../../lib/libft/ft_2dstr_len.c
#     ../../lib/libft/ft_atof.c
#     ../../lib/libft/ft_arr2d_free.c
#     ../../lib/libft/ft_calloc.c
#     ../../lib/libft/ft_itoa.c
#     ../../lib/libft/ft_strncmp.c
#     ../../lib/libft/ft_bzero.c
#     ../../lib/libft/ft_strlen.c
#     ../../lib/libft/check_for_overflow.c
#     ../../lib/libft/ft_atof.c
#     ../../lib/libft/ft_isdigit.c)

# target_link_libraries(check_vector PRIVATE gtest gtest_main)
# target_compile_features(check_vector PRIVATE cxx_std_17)
# gtest_discover_tests(check_vector)

# # add_executable(validate_camera validate_camera.cpp 
# #     ../../src/parse/validate_settings.c
# #     ../../src/parse/validate_utils.c
# #     ../../lib/libft/ft_atoi.c
# #     ../../lib/libft/ft_split.c
# #     ../../lib/libft/ft_2dstr_len.c
# #     ../../lib/libft/ft_atof.c
# #     ../../lib/libft/ft_arr2d_free.c
# #     ../../lib/libft/ft_calloc.c
# #     ../../lib/libft/ft_itoa.c
# #     ../../lib/libft/ft_strncmp.c
# #     ../../lib/libft/ft_bzero.c
# #     ../../lib/libft/ft_strlen.c
# #     ../../lib/libft/check_for_overflow.c
# #     ../../lib/libft/ft_atof.c
# #     ../../lib/libft/ft_isdigit.c)

# # target_link_libraries(validate_camera PRIVATE gtest gtest_main)
# # target_compile_features(validate_camera PRIVATE cxx_std_17)
# # gtest_discover_tests(validate_camera)

# add_executable(validate_light validate_light.cpp 
#     ../../src/parse/validate_settings.c
#     ../../src/parse/validate_utils.c
#     ../../lib/libft/ft_atoi.c
#     ../../lib/libft/ft_split.c
#     ../../lib/libft/ft_2dstr_len.c
#     ../../lib/libft/ft_atof.c
#     ../../lib/libft/ft_arr2d_free.c
#     ../../lib/libft/ft_calloc.c
#     ../../lib/libft/ft_itoa.c
#     ../../lib/libft/ft_strncmp.c
#     ../../lib/libft/ft_bzero.c
#     ../../lib/libft/ft_strlen.c
#     ../../lib/libft/check_for_overflow.c
#     ../../lib/libft/ft_atof.c
#     ../../lib/libft/ft_isdigit.c)

# target_link_libraries(validate_light PRIVATE gtest gtest_main)
# target_compile_features(validate_light PRIVATE cxx_std_17)
# gtest_discover_tests(validate_light)

add_executable(validate_file validate_file.cpp
    ../../src/parse/validate_file.c
    ../../src/parse/validate_utils.c
    ../../lib/libft/ft_atoi.c
    ../../lib/libft/ft_split.c
    ../../lib/libft/ft_2dstr_len.c
    ../../lib/libft/ft_atof.c
    ../../lib/libft/ft_arr2d_free.c
    ../../lib/libft/ft_calloc.c
    ../../lib/libft/ft_itoa.c
    ../../lib/libft/ft_strncmp.c
    ../../lib/libft/ft_bzero.c
    ../../lib/libft/ft_strlen.c
    ../../lib/libft/check_for_overflow.c
    ../../lib/libft/ft_atof.c
    ../../lib/libft/ft_isdigit.c)

target_link_libraries(validate_file PRIVATE gtest gtest_main)
target_compile_features(validate_file PRIVATE cxx_std_17)
gtest_discover_tests(validate_file)


target_link_libraries(validate_settings PRIVATE gtest gtest_main)
target_compile_features(validate_settings PRIVATE cxx_std_17)
gtest_discover_tests(validate_settings)