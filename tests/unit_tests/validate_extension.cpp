#include <gtest/gtest.h>
#include <cstdlib>
#include <sstream>
#include <string>

extern "C"
{
    #include "../inc/parser.h"
}

TEST(validate_extension, invalid_extension) {
    char *filepath = "testfile.txt";
    int result = check_extension(filepath);
    EXPECT_EQ(result, -1);
}

TEST(validate_extension, valid_extension) {
    char *filepath = "testfile.rt";
    int result = check_extension(filepath);
    EXPECT_EQ(result, 0);
}

TEST(validate_extension, empty_filepath) {
    char *filepath = "";
    int result = check_extension(filepath);
    EXPECT_EQ(result, -1);
}

TEST(validate_extension, null_filepath) {
    char *filepath = NULL;
    int result = check_extension(filepath);
    EXPECT_EQ(result, -1);
}

TEST(validate_extension, invalid_extension2) {
    char *filepath = "testfile.rtt";
    int result = check_extension(filepath);
    EXPECT_EQ(result, -1);
}

TEST(validate_extension, only_extension) {
    char *filepath = ".rt";
    int result = check_extension(filepath);
    EXPECT_EQ(result, -1);
}

TEST(validate_extension, extension_in_the_middle) {
    char *filepath = "te.rtst.rt";
    int result = check_extension(filepath);
    EXPECT_EQ(result, -1);
}

TEST(validate_extension, extension_at_the_end) {
    char *filepath = "testfile.rt.";
    int result = check_extension(filepath);
    EXPECT_EQ(result, -1);
}

TEST(validate_extension, doubledot) {
    char *filepath = "test..rt";
    int result = check_extension(filepath);
    EXPECT_EQ(result, -1);
}

TEST(validate_extension, no_extension) {
    char *filepath = "testfile";
    int result = check_extension(filepath);
    EXPECT_EQ(result, -1);
}

TEST(validate_extension, hidden_file_with_valid_extension) {
    char *filepath = ".testfile.rt";
    int result = check_extension(filepath);
    EXPECT_EQ(result, 0);
}

TEST(validate_extension, hidden_file_without_extension) {
    char *filepath = ".testfile";
    int result = check_extension(filepath);
    EXPECT_EQ(result, -1);
}

TEST(validate_extension, valid_extension_with_uppercase) {
    char *filepath = "testfile.RT";
    int result = check_extension(filepath);
    EXPECT_EQ(result, -1);
}

TEST(validate_extension, long_filename_with_valid_extension) {
    char *filepath = "averylongfilenamefortestingpurposes.rt";
    int result = check_extension(filepath);
    EXPECT_EQ(result, 0);
}

TEST(validate_extension, special_characters_in_filename) {
    char *filepath = "test$file@!.rt";
    int result = check_extension(filepath);
    EXPECT_EQ(result, 0);
}

TEST(validate_extension, special_characters_without_extension) {
    char *filepath = "test$file@!";
    int result = check_extension(filepath);
    EXPECT_EQ(result, -1);
}

TEST(validate_extension, spaces_in_filename_valid_extension) {
    char *filepath = "test file.rt";
    int result = check_extension(filepath);
    EXPECT_EQ(result, 0);
}

TEST(validate_extension, spaces_in_filename_invalid_extension) {
    char *filepath = "test file.txt";
    int result = check_extension(filepath);
    EXPECT_EQ(result, -1);
}

TEST(validate_extension, extension_with_extra_period) {
    char *filepath = "testfile.rt.";
    int result = check_extension(filepath);
    EXPECT_EQ(result, -1);
}

TEST(validate_extension, extension_with_trailing_spaces) {
    char *filepath = "testfile.rt   ";
    int result = check_extension(filepath);
    EXPECT_EQ(result, -1);
}

TEST(validate_extension, valid_extension_with_leading_spaces) {
    char *filepath = "   testfile.rt";
    int result = check_extension(filepath);
    EXPECT_EQ(result, 0);
}

TEST(validate_extension, numeric_filename_with_valid_extension) {
    char *filepath = "123456.rt";
    int result = check_extension(filepath);
    EXPECT_EQ(result, 0);
}

TEST(validate_extension, numeric_filename_without_extension) {
    char *filepath = "123456";
    int result = check_extension(filepath);
    EXPECT_EQ(result, -1);
}

TEST(validate_extension, very_large_filename) {
    char filepath[300];
    memset(filepath, 'a', 295);
    strcpy(filepath + 295, ".rt");
    int result = check_extension(filepath);
    EXPECT_EQ(result, 0);
}

TEST(validate_extension, null_character_in_filename) {
    char filepath[] = "testfile.rt\0hidden.txt";
    int result = check_extension(filepath);
    EXPECT_EQ(result, 0);
}

