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
    char *colors = "0,0,0";
    EXPECT_EQ(0, check_colors(colors));
}

TEST(validate_colors, valid_colors_2) {
    char *colors = "255,255,255";
    EXPECT_EQ(0, check_colors(colors));
}

TEST(validate_colors, valid_colors_3) {
    char *colors = "123,45,67";
    EXPECT_EQ(0, check_colors(colors));
}

TEST(validate_colors, missing_component) {
    char *colors = "255,255";
    EXPECT_EQ(-1, check_colors(colors));
}

TEST(validate_colors, extra_component) {
    char *colors = "255,255,255,255";
    EXPECT_EQ(-1, check_colors(colors));
}

TEST(validate_colors, empty_string) {
    char *colors = "";
    EXPECT_EQ(-1, check_colors(colors));
}

TEST(validate_colors, only_commas) {
    char *colors = ",,,";
    EXPECT_EQ(-1, check_colors(colors));
}

TEST(validate_colors, negative_value) {
    char *colors = "-1,0,0";
    EXPECT_EQ(-1, check_colors(colors));
}

TEST(validate_colors, over_255) {
    char *colors = "256,100,100";
    EXPECT_EQ(-1, check_colors(colors));
}

TEST(validate_colors, all_values_invalid) {
    char *colors = "-5,500,300";
    EXPECT_EQ(-1, check_colors(colors));
}

TEST(validate_colors, integer_overflow_positive) {
    char *colors = "9999999999,50,50";
    EXPECT_EQ(-1, check_colors(colors));
}

TEST(validate_colors, integer_overflow_negative) {
    char *colors = "-9999999999,50,50";
    EXPECT_EQ(-1, check_colors(colors));
}

TEST(validate_colors, contains_letters) {
    char *colors = "1a,2b,3c";
    EXPECT_EQ(-1, check_colors(colors));
}

TEST(validate_colors, special_characters) {
    char *colors = "!,@,#";
    EXPECT_EQ(-1, check_colors(colors));
}

TEST(validate_colors, spaces_between_numbers) {
    char *colors = " 10 , 20 , 30 ";
    EXPECT_EQ(-1, check_colors(colors));
}

TEST(validate_colors, spaces_without_numbers) {
    char *colors = " , , ";
    EXPECT_EQ(-1, check_colors(colors));
}

TEST(validate_colors, leading_and_trailing_spaces) {
    char *colors = " 255,255,255 ";
    EXPECT_EQ(-1, check_colors(colors));
}

TEST(validate_colors, single_number) {
    char *colors = "42";
    EXPECT_EQ(-1, check_colors(colors));
}

TEST(validate_colors, only_delimiters) {
    char *colors = ",,";
    EXPECT_EQ(-1, check_colors(colors));
}

TEST(validate_colors, valid_values_with_extra_comma) {
    char *colors = "200,150,100,";
    EXPECT_EQ(-1, check_colors(colors));
}

TEST(validate_colors, max_boundary) {
    char *colors = "255,255,255";
    EXPECT_EQ(0, check_colors(colors));
}

TEST(validate_colors, min_boundary) {
    char *colors = "0,0,0";
    EXPECT_EQ(0, check_colors(colors));
}
