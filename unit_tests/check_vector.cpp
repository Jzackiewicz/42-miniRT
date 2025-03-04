#include <gtest/gtest.h>
#include <cstdlib>
#include <sstream>
#include <string>

extern "C"
{
    #include "../inc/parser.h"
}

#include <gtest/gtest.h>

extern "C" {
    int	check_vector(char *vector);
}

TEST(CheckVectorTest, ValidVectors) {
    EXPECT_EQ(check_vector((char *)"1.0,0.0,0.0"), 0);  // Unit vector along X-axis
    EXPECT_EQ(check_vector((char *)"0.0,1.0,0.0"), 0);  // Unit vector along Y-axis
    EXPECT_EQ(check_vector((char *)"0.0,0.0,1.0"), 0);  // Unit vector along Z-axis
    EXPECT_EQ(check_vector((char *)"-0.7071,0.7071,0.0"), 0); // Diagonal unit vector
}

TEST(CheckVectorTest, InvalidRange) {
    EXPECT_EQ(check_vector((char *)"1.1,0.0,0.0"), -1);  // Out of range
    EXPECT_EQ(check_vector((char *)"0.0,-1.1,0.0"), -1); // Out of range
    EXPECT_EQ(check_vector((char *)"0.5,0.5,1.2"), -1);  // One value too large
}

TEST(CheckVectorTest, NotNormalized) {
    EXPECT_EQ(check_vector((char *)"0.5,0.5,0.5"), -1);  // Magnitude is not 1
    EXPECT_EQ(check_vector((char *)"2.0,0.0,0.0"), -1);  // Too large
    EXPECT_EQ(check_vector((char *)"0.3,0.3,0.3"), -1);  // Not a unit vector
}

TEST(CheckVectorTest, InvalidFormat) {
    EXPECT_EQ(check_vector((char *)""), -1);            // Empty string
    EXPECT_EQ(check_vector((char *)"0.5,,"), -1);       // Malformed input
    EXPECT_EQ(check_vector((char *)"0.5 0.5 0.5"), -1); // No commas
    EXPECT_EQ(check_vector((char *)"0.5,abc,0.5"), -1); // Non-numeric value
    EXPECT_EQ(check_vector((char *)"NaN,0.5,0.5"), -1); // Invalid float
}

TEST(CheckVectorTest, EdgeCaseValidVectors) {
    EXPECT_EQ(check_vector((char *)"1.0,0.0,0.0"), 0);      // X-axis unit vector
    EXPECT_EQ(check_vector((char *)"0.0,1.0,0.0"), 0);      // Y-axis unit vector
    EXPECT_EQ(check_vector((char *)"0.0,0.0,1.0"), 0);      // Z-axis unit vector
    EXPECT_EQ(check_vector((char *)"-1.0,0.0,0.0"), 0);     // Negative X-axis
    EXPECT_EQ(check_vector((char *)"0.0,-1.0,0.0"), 0);     // Negative Y-axis
    EXPECT_EQ(check_vector((char *)"0.0,0.0,-1.0"), 0);     // Negative Z-axis
    EXPECT_EQ(check_vector((char *)"0.5774,0.5774,0.5774"), 0); // Normalized diagonal vector
    EXPECT_EQ(check_vector((char *)"-0.7071,-0.7071,0.0"), 0);  // Negative diagonal
}

TEST(CheckVectorTest, FloatingPointPrecision) {
    EXPECT_EQ(check_vector((char *)"0.999999,0.0,0.0"), 0); // Just under 1
    EXPECT_EQ(check_vector((char *)"-0.999999,0.0,0.0"), 0);
    EXPECT_EQ(check_vector((char *)"0.70710678,0.70710678,0.0"), 0); // sqrt(2)/2 normalized
    EXPECT_EQ(check_vector((char *)"0.57735,0.57735,0.57735"), 0);   // sqrt(1/3) normalized
}

TEST(CheckVectorTest, MalformedInputs) {
    EXPECT_EQ(check_vector((char *)""), -1);            // Empty string
    EXPECT_EQ(check_vector((char *)" "), -1);           // Space only
    EXPECT_EQ(check_vector((char *)","), -1);           // Just a comma
    EXPECT_EQ(check_vector((char *)"0.5,,"), -1);       // Extra comma
    EXPECT_EQ(check_vector((char *)",0.5,0.5"), -1);    // Leading comma
    EXPECT_EQ(check_vector((char *)"0.5,0.5,0.5,"), -1);// Trailing comma
    EXPECT_EQ(check_vector((char *)"0.5 0.5 0.5"), -1); // Missing commas
    EXPECT_EQ(check_vector((char *)"0.5,abc,0.5"), -1); // Non-numeric value
    EXPECT_EQ(check_vector((char *)"NaN,0.5,0.5"), -1); // NaN-like value
    EXPECT_EQ(check_vector((char *)"0.5,,0.5"), -1);    // Empty field
}

TEST(CheckVectorTest, OutOfRangeValues) {
    EXPECT_EQ(check_vector((char *)"1.1,0.0,0.0"), -1);    // Out of range > 1.0
    EXPECT_EQ(check_vector((char *)"-1.1,0.0,0.0"), -1);   // Out of range < -1.0
    EXPECT_EQ(check_vector((char *)"0.5,0.5,1.5"), -1);    // One value too high
    EXPECT_EQ(check_vector((char *)"-2.0,0.0,0.0"), -1);   // Way out of range
}

TEST(CheckVectorTest, NotNormalized2) {
    EXPECT_EQ(check_vector((char *)"0.5,0.5,0.5"), -1);  // Magnitude not 1
    EXPECT_EQ(check_vector((char *)"0.1,0.1,0.1"), -1);  // Magnitude too small
    EXPECT_EQ(check_vector((char *)"0.9,0.9,0.9"), -1);  // Way too large
    EXPECT_EQ(check_vector((char *)"2.0,0.0,0.0"), -1);  // Out of range
    EXPECT_EQ(check_vector((char *)"0.3,0.3,0.3"), -1);  // Not a unit vector
}

TEST(CheckVectorTest, SpecialCharacters) {
    EXPECT_EQ(check_vector((char *)"@,0.5,0.5"), -1);    // Invalid character
    EXPECT_EQ(check_vector((char *)"0.5,#,0.5"), -1);
    EXPECT_EQ(check_vector((char *)"0.5,0.5,$"), -1);
    EXPECT_EQ(check_vector((char *)"0.5,\n,0.5"), -1);   // Newline character
}
