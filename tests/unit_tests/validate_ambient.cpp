#include <gtest/gtest.h>
#include <cstdlib>
#include <sstream>
#include <string>

extern "C"
{
    #include "../inc/parser.h"
}

TEST(validate_ambient, valid_input) {
    char *line = "A 0.5 255,255,255";
    char **line_split = ft_split(line, ' ');
    EXPECT_EQ(0, validate_ambient(line_split, line));
}

TEST(validate_ambient, valid_min_float) {
    char *line = "A 0.0 0,0,0";
    char **line_split = ft_split(line, ' ');
    EXPECT_EQ(0, validate_ambient(line_split, line));
}

TEST(validate_ambient, valid_max_float) {
    char *line = "A 1.0 255,255,255";
    char **line_split = ft_split(line, ' ');
    EXPECT_EQ(0, validate_ambient(line_split, line));
}

TEST(validate_ambient, negative_float) {
    char *line = "A -0.1 255,255,255";
    char **line_split = ft_split(line, ' ');
    EXPECT_EQ(-1, validate_ambient(line_split, line));
}

TEST(validate_ambient, float_above_one) {
    char *line = "A 1.1 255,255,255";
    char **line_split = ft_split(line, ' ');
    EXPECT_EQ(-1, validate_ambient(line_split, line));
}

TEST(validate_ambient, non_numeric_float) {
    char *line = "A abc 255,255,255";
    char **line_split = ft_split(line, ' ');
    EXPECT_EQ(-1, validate_ambient(line_split, line));
}

TEST(validate_ambient, missing_color_component) {
    char *line = "A 0.5 255,255";
    char **line_split = ft_split(line, ' ');
    EXPECT_EQ(-1, validate_ambient(line_split, line));
}

TEST(validate_ambient, extra_color_component) {
    char *line = "A 0.5 255,255,255,100";
    char **line_split = ft_split(line, ' ');
    EXPECT_EQ(-1, validate_ambient(line_split, line));
}

TEST(validate_ambient, non_numeric_color) {
    char *line = "A 0.5 255,abc,255";
    char **line_split = ft_split(line, ' ');
    EXPECT_EQ(-1, validate_ambient(line_split, line));
}

TEST(validate_ambient, color_below_zero) {
    char *line = "A 0.5 -10,255,255";
    char **line_split = ft_split(line, ' ');
    EXPECT_EQ(-1, validate_ambient(line_split, line));
}

TEST(validate_ambient, color_above_255) {
    char *line = "A 0.5 255,256,255";
    char **line_split = ft_split(line, ' ');
    EXPECT_EQ(-1, validate_ambient(line_split, line));
}

TEST(validate_ambient, missing_spaces) {
    char *line = "A0.5 255,255,255";
    char **line_split = ft_split(line, ' ');
    EXPECT_EQ(-1, validate_ambient(line_split, line));
}

TEST(validate_ambient, missing_identifier) {
    char *line = "0.5 255,255,255";
    char **line_split = ft_split(line, ' ');
    EXPECT_EQ(-1, validate_ambient(line_split, line));
}

TEST(validate_ambient, empty_string) {
    char *line = "";
    char **line_split = ft_split(line, ' ');
    EXPECT_EQ(-1, validate_ambient(line_split, line));
}

TEST(validate_ambient, null_string) {
    char *line = NULL;
    char **line_split = NULL;
    EXPECT_EQ(-1, validate_ambient(line_split, line));
}
