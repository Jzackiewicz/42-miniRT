#include <gtest/gtest.h>

extern "C" {
    int validate_camera(char **line_split, char *line);
}

TEST(ValidateCameraTest, ValidCameras) {
    char *valid1[] = {(char *)"C", (char *)"-50.0,0,20", (char *)"0,0,1", (char *)"70", NULL};
    char *valid2[] = {(char *)"C", (char *)"0,0,0", (char *)"1,0,0", (char *)"90", NULL};
    char *valid3[] = {(char *)"C", (char *)"10,10,10", (char *)"0.7071,0.7071,0", (char *)"45", NULL};
    EXPECT_EQ(validate_camera(valid1, (char *)"C -50.0,0,20 0,0,1 70"), 0);
    EXPECT_EQ(validate_camera(valid2, (char *)"C 0,0,0 1,0,0 90"), 0);
    EXPECT_EQ(validate_camera(valid3, (char *)"C 10,10,10 0.707,0.707,0 45"), 0);
}

TEST(ValidateCameraTest, InvalidCoordinates) {
    char *invalid1[] = {(char *)"C", (char *)"abc,0,20", (char *)"0,0,1", (char *)"70", NULL};  // Non-numeric
    char *invalid2[] = {(char *)"C", (char *)"0,0,", (char *)"0,0,1", (char *)"70", NULL};     // Malformed
    EXPECT_EQ(validate_camera(invalid1, (char *)"C abc,0,20 0,0,1 70"), -1);
    EXPECT_EQ(validate_camera(invalid2, (char *)"C 0,0, 0,0,1 70"), -1);
}

TEST(ValidateCameraTest, InvalidVectors) {
    char *invalid1[] = {(char *)"C", (char *)"0,0,0", (char *)"1,1,1", (char *)"60", NULL};    // Not normalized
    char *invalid2[] = {(char *)"C", (char *)"0,0,0", (char *)"1.5,0,0", (char *)"45", NULL};  // Out of range
    char *invalid3[] = {(char *)"C", (char *)"0,0,0", (char *)"0.5,,0.5", (char *)"45", NULL}; // Malformed
    EXPECT_EQ(validate_camera(invalid1, (char *)"C 0,0,0 1,1,1 60"), -1);
    EXPECT_EQ(validate_camera(invalid2, (char *)"C 0,0,0 1.5,0,0 45"), -1);
    EXPECT_EQ(validate_camera(invalid3, (char *)"C 0,0,0 0.5,,0.5 45"), -1);
}

TEST(ValidateCameraTest, InvalidFOV) {
    char *invalid1[] = {(char *)"C", (char *)"0,0,0", (char *)"0,0,1", (char *)"190", NULL}; // FOV > 180
    char *invalid2[] = {(char *)"C", (char *)"0,0,0", (char *)"0,0,1", (char *)"-10", NULL}; // FOV < 0
    char *invalid3[] = {(char *)"C", (char *)"0,0,0", (char *)"0,0,1", (char *)"abc", NULL}; // Non-numeric
    EXPECT_EQ(validate_camera(invalid1, (char *)"C 0,0,0 0,0,1 190"), -1);
    EXPECT_EQ(validate_camera(invalid2, (char *)"C 0,0,0 0,0,1 -10"), -1);
    EXPECT_EQ(validate_camera(invalid3, (char *)"C 0,0,0 0,0,1 abc"), -1);
}

TEST(ValidateCameraTest, MalformedInput) {
    char *invalid1[] = {(char *)"C", (char *)"0,0,0", (char *)"0,0,1", NULL}; // Missing FOV
    char *invalid2[] = {(char *)"C", (char *)"0,0,0", NULL};                 // Missing vector and FOV
    char *invalid3[] = {NULL};                                               // Empty input
    EXPECT_EQ(validate_camera(invalid1, (char *)"C 0,0,0 0,0,1"), -1);
    EXPECT_EQ(validate_camera(invalid2, (char *)"C 0,0,0"), -1);
    EXPECT_EQ(validate_camera(invalid3, (char *)""), -1);
}

TEST(ValidateCameraTest, RejectsInvalidSpacing) {
    char *invalid1[] = {(char *)"C", (char *)" , 0, 20 ", (char *)" 0, 0, 1 ", (char *)" 70 ", NULL};  // Comma at start
    char *invalid2[] = {(char *)"C", (char *)" 0, 0, 20 ", (char *)" 0,  , 1 ", (char *)" 70 ", NULL}; // Missing vector part
    EXPECT_EQ(validate_camera(invalid1, (char *)"C  , 0, 20   0, 0, 1   70 "), -1);
    EXPECT_EQ(validate_camera(invalid2, (char *)"C  0, 0, 20   0,  , 1   70 "), -1);
}
