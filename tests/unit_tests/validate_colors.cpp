#include <gtest/gtest.h>
#include <cstdlib>
#include <sstream>
#include <string>

extern "C"
{
    #include "../inc/parser.h"
}

#include <gtest/gtest.h>
#include <cstdlib>
#include <sstream>
#include <string>

extern "C"
{
    #include "../inc/parser.h"
}

TEST(validate_colors, valid_colors_1) {
    char *color = "0,0,0";
    EXPECT_EQ(0, check_colors(color));
}

TEST(validate_colors, valid_colors_2) {
    char *color = "255,255,255";
    EXPECT_EQ(0, check_colors(color));
}

TEST(validate_colors, valid_colors_3) {
    char *color = "123,45,67";
    EXPECT_EQ(0, check_colors(color));
}

TEST(validate_colors, missing_component) {
    char *color = "255,255";
    EXPECT_EQ(-1, check_colors(color));
}

TEST(validate_colors, extra_component) {
    char *color = "255,255,255,255";
    EXPECT_EQ(-1, check_colors(color));
}

TEST(validate_colors, empty_string) {
    char *color = "";
    EXPECT_EQ(-1, check_colors(color));
}

TEST(validate_colors, only_commas) {
    char *color = ",,,";
    EXPECT_EQ(-1, check_colors(color));
}

TEST(validate_colors, negative_value) {
    char *color = "-1,0,0";
    EXPECT_EQ(-1, check_colors(color));
}

TEST(validate_colors, over_255) {
    char *color = "256,100,100";
    EXPECT_EQ(-1, check_colors(color));
}

TEST(validate_colors, all_values_invalid) {
    char *color = "-5,500,300";
    EXPECT_EQ(-1, check_colors(color));
}

TEST(validate_colors, integer_overflow_positive) {
    char *color = "9999999999,50,50";
    EXPECT_EQ(-1, check_colors(color));
}

TEST(validate_colors, integer_overflow_negative) {
    char *color = "-9999999999,50,50";
    EXPECT_EQ(-1, check_colors(color));
}

TEST(validate_colors, contains_letters) {
    char *color = "1a,2b,3c";
    EXPECT_EQ(-1, check_colors(color));
}

TEST(validate_colors, special_characters) {
    char *color = "!,@,#";
    EXPECT_EQ(-1, check_colors(color));
}

TEST(validate_colors, spaces_between_numbers) {
    char *color = " 10 , 20 , 30 ";
    EXPECT_EQ(-1, check_colors(color));
}

TEST(validate_colors, spaces_without_numbers) {
    char *color = " , , ";
    EXPECT_EQ(-1, check_colors(color));
}

TEST(validate_colors, leading_and_trailing_spaces) {
    char *color = " 255,255,255 ";
    EXPECT_EQ(-1, check_colors(color));
}

TEST(validate_colors, single_number) {
    char *color = "42";
    EXPECT_EQ(-1, check_colors(color));
}

TEST(validate_colors, only_delimiters) {
    char *color = ",,";
    EXPECT_EQ(-1, check_colors(color));
}

TEST(validate_colors, valid_values_with_extra_comma) {
    char *color = "200,150,100,";
    EXPECT_EQ(-1, check_colors(color));
}

TEST(validate_colors, max_boundary) {
    char *color = "255,255,255";
    EXPECT_EQ(0, check_colors(color));
}

TEST(validate_colors, min_boundary) {
    char *color = "0,0,0";
    EXPECT_EQ(0, check_colors(color));
}
