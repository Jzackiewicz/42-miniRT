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
    int check_coords(char *coords);
}

TEST(CheckcoordsTest, Validcoords) {
    EXPECT_EQ(check_coords((char *)"1.23,-4.56,7.89"), 0);
    EXPECT_EQ(check_coords((char *)"0.0,0.0,0.0"), 0);
    EXPECT_EQ(check_coords((char *)"-100.5,200.2,50.1"), 0);
}

TEST(CheckcoordsTest, InvalidFormat) {
    EXPECT_EQ(check_coords((char *)""), -1);               // Empty string
    EXPECT_EQ(check_coords((char *)","), -1);              // Only delimiter
    EXPECT_EQ(check_coords((char *)"1.0,2.0,"), -1);       // Trailing comma
    EXPECT_EQ(check_coords((char *)"1.0,2.0,3.0,"), -1);   // Extra comma
    EXPECT_EQ(check_coords((char *)"1.0 2.0 3.0"), -1);    // Missing commas
}

TEST(CheckcoordsTest, InvalidNumberOfComponents) {
    EXPECT_EQ(check_coords((char *)"1.23,-4.56"), -1);        // Only two numbers
    EXPECT_EQ(check_coords((char *)"1.23,-4.56,7.89,0.0"), -1); // Four numbers
}

TEST(CheckcoordsTest, InvalidFloatValues) {
    EXPECT_EQ(check_coords((char *)"abc,0.5,0.4"), -1);    // Non-numeric value
    EXPECT_EQ(check_coords((char *)"0.5,NaN,0.4"), -1);    // NaN-like value
    EXPECT_EQ(check_coords((char *)"0.5,.,0.4"), -1);      // Single dot
}
