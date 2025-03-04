#include <gtest/gtest.h>
#include <cstdlib>
#include <sstream>
#include <string>

extern "C"
{
    #include "../inc/parser.h"
}

TEST(ValidateLightTest, ValidInputs) {
    char *valid1[] = {(char *)"L", (char *)"-40.0,50.0,0.0", (char *)"0.6", (char *)"10,0,255", NULL};
    char *valid2[] = {(char *)"L", (char *)"0,0,0", (char *)"1.0", (char *)"255,255,255", NULL};
    char *valid3[] = {(char *)"L", (char *)"30.5,-20.2,15.1", (char *)"0.0", (char *)"0,0,0", NULL};

    EXPECT_EQ(validate_light(valid1, (char *)"L -40.0,50.0,0.0 0.6 10,0,255"), 0);
    EXPECT_EQ(validate_light(valid2, (char *)"L 0,0,0 1.0 255,255,255"), 0);
    EXPECT_EQ(validate_light(valid3, (char *)"L 30.5,-20.2,15.1 0.0 0,0,0"), 0);
}

TEST(ValidateLightTest, InvalidCoordinates) {
    char *invalid1[] = {(char *)"L", (char *)"-40.0, 50.0", (char *)"0.6", (char *)"10,0,255", NULL};  // Missing Z coord
    char *invalid2[] = {(char *)"L", (char *)"-40.0,50.0,abc", (char *)"0.6", (char *)"10,0,255", NULL};  // Invalid Z coord

    EXPECT_EQ(validate_light(invalid1, (char *)"L -40.0, 50.0 0.6 10,0,255"), -1);
    EXPECT_EQ(validate_light(invalid2, (char *)"L -40.0,50.0,abc 0.6 10,0,255"), -1);
}

TEST(ValidateLightTest, InvalidBrightness) {
    char *invalid1[] = {(char *)"L", (char *)"-40.0,50.0,0.0", (char *)"-0.1", (char *)"10,0,255", NULL};  // Below 0.0
    char *invalid2[] = {(char *)"L", (char *)"-40.0,50.0,0.0", (char *)"1.1", (char *)"10,0,255", NULL};  // Above 1.0
    char *invalid3[] = {(char *)"L", (char *)"-40.0,50.0,0.0", (char *)"abc", (char *)"10,0,255", NULL};  // Not a number

    EXPECT_EQ(validate_light(invalid1, (char *)"L -40.0,50.0,0.0 -0.1 10,0,255"), -1);
    EXPECT_EQ(validate_light(invalid2, (char *)"L -40.0,50.0,0.0 1.1 10,0,255"), -1);
    EXPECT_EQ(validate_light(invalid3, (char *)"L -40.0,50.0,0.0 abc 10,0,255"), -1);
}

TEST(ValidateLightTest, InvalidRGB) {
    char *invalid1[] = {(char *)"L", (char *)"-40.0,50.0,0.0", (char *)"0.6", (char *)"256,0,255", NULL};  // R > 255
    char *invalid2[] = {(char *)"L", (char *)"-40.0,50.0,0.0", (char *)"0.6", (char *)"10,-1,255", NULL};  // G < 0
    char *invalid3[] = {(char *)"L", (char *)"-40.0,50.0,0.0", (char *)"0.6", (char *)"10,0,abc", NULL};  // B not a number

    EXPECT_EQ(validate_light(invalid1, (char *)"L -40.0,50.0,0.0 0.6 256,0,255"), -1);
    EXPECT_EQ(validate_light(invalid2, (char *)"L -40.0,50.0,0.0 0.6 10,-1,255"), -1);
    EXPECT_EQ(validate_light(invalid3, (char *)"L -40.0,50.0,0.0 0.6 10,0,abc"), -1);
}

TEST(ValidateLightTest, HandlesExtraSpaces) {
    char *valid1[] = {(char *)"L", (char *)"-40.0,50.0,0.0", (char *)"0.6", (char *)"10,0,255", NULL};

    EXPECT_EQ(validate_light(valid1, (char *)"L   -40.0,50.0,0.0    0.6    10,0,255   "), 0);
}

TEST(ValidateLightTest, HandlesExtremeValues) {
    char *valid1[] = {(char *)"L", (char *)"-1000.0,1000.0,-1000.0", (char *)"1.0", (char *)"255,255,255", NULL}; // Large valid coordinates
    char *valid2[] = {(char *)"L", (char *)"0.00001,-0.00001,0.00001", (char *)"0.0", (char *)"0,0,0", NULL}; // Small valid coordinates

    EXPECT_EQ(validate_light(valid1, (char *)"L -1000.0,1000.0,-1000.0 1.0 255,255,255"), 0);
    EXPECT_EQ(validate_light(valid2, (char *)"L 0.00001, -0.00001, 0.00001 0.0 0,0,0"), 0);
}

TEST(ValidateLightTest, InvalidExtraArguments) {
    char *invalid1[] = {(char *)"L", (char *)"-40.0,50.0,0.0", (char *)"0.6", (char *)"10,0,255", (char *)"extra", NULL}; // Too many arguments

    EXPECT_EQ(validate_light(invalid1, (char *)"L -40.0,50.0,0.0 0.6 10,0,255 extra"), -1);
}

TEST(ValidateLightTest, MissingArguments) {
    char *invalid1[] = {(char *)"L", (char *)"-40.0,50.0,0.0", (char *)"0.6", NULL};
    char *invalid2[] = {(char *)"L", (char *)"-40.0,50.0,0.0", NULL};
    char *invalid3[] = {(char *)"L", NULL};

    EXPECT_EQ(validate_light(invalid1, (char *)"L -40.0,50.0,0.0 0.6"), -1);
    EXPECT_EQ(validate_light(invalid2, (char *)"L -40.0,50.0,0.0"), -1);
    EXPECT_EQ(validate_light(invalid3, (char *)"L"), -1);
}

TEST(ValidateLightTest, NonNumericCharactersInParameters) {
    char *invalid1[] = {(char *)"L", (char *)"-40.0,50.0,xyz", (char *)"0.6", (char *)"10,0,255", NULL}; // Invalid coordinate
    char *invalid2[] = {(char *)"L", (char *)"-40.0,50.0,0.0", (char *)"1O.O", (char *)"10,0,255", NULL}; // Invalid brightness (letter O instead of 0)
    char *invalid3[] = {(char *)"L", (char *)"-40.0,50.0,0.0", (char *)"0.6", (char *)"255,abc,255", NULL}; // Invalid color

    EXPECT_EQ(validate_light(invalid1, (char *)"L -40.0,50.0,xyz 0.6 10,0,255"), -1);
    EXPECT_EQ(validate_light(invalid2, (char *)"L -40.0,50.0,0.0 1O.O 10,0,255"), -1);
    EXPECT_EQ(validate_light(invalid3, (char *)"L -40.0,50.0,0.0 0.6 255,abc,255"), -1);
}

TEST(ValidateLightTest, ExcessOrMissingCommas) {
    char *invalid1[] = {(char *)"L", (char *)"-40.0,50.0,,0.0", (char *)"0.6", (char *)"10,0,255", NULL}; // Extra comma in coordinates
    char *invalid2[] = {(char *)"L", (char *)"-40.0,50.0,0.0", (char *)"0.6", (char *)"10,0255", NULL}; // Missing comma in color

    EXPECT_EQ(validate_light(invalid1, (char *)"L -40.0,50.0,,0.0 0.6 10,0,255"), 0);
    EXPECT_EQ(validate_light(invalid2, (char *)"L -40.0,50.0,0.0 0.6 10,0255"), -1);
}

TEST(ValidateLightTest, EdgeCaseFloatingPointValues) {
    char *valid1[] = {(char *)"L", (char *)"0.0,0.0,0.0", (char *)"0.0000001", (char *)"0,0,0", NULL}; // Very small brightness
    char *invalid1[] = {(char *)"L", (char *)"0.0,0.0,0.0", (char *)"-0.0000001", (char *)"0,0,0", NULL}; // Negative brightness

    EXPECT_EQ(validate_light(valid1, (char *)"L 0.0,0.0,0.0 0.0000001 0,0,0"), 0);
    EXPECT_EQ(validate_light(invalid1, (char *)"L 0.0,0.0,0.0 -0.0000001 0,0,0"), -1);
}
