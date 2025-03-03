#include <gtest/gtest.h>
#include <cstdlib>
#include <sstream>
#include <string>

extern "C"
{
    #include "../inc/parser.h"
}


TEST(validate_file, invalid_extension) {
    char *filepath = "testfile.txt";
    int result = check_extension(filepath);
    EXPECT_EQ(result, -1);
}

TEST(validate_file, valid_extension) {
    char *filepath = "testfile.rt";
    int result = check_extension(filepath);
    EXPECT_EQ(result, 0);
}

TEST(validate_file, empty_filepath) {
    char *filepath = "";
    int result = check_extension(filepath);
    EXPECT_EQ(result, -1);
}

TEST(validate_file, null_filepath) {
    char *filepath = NULL;
    int result = check_extension(filepath);
    EXPECT_EQ(result, -1);
}

TEST(validate_file, invalid_extension2) {
    char *filepath = "testfile.rtt";
    int result = check_extension(filepath);
    EXPECT_EQ(result, -1);
}

TEST(validate_file, only_extension) {
    char *filepath = ".rt";
    int result = check_extension(filepath);
    EXPECT_EQ(result, -1);
}

TEST(validate_file, extension_in_the_middle) {
    char *filepath = "te.rtst.rt";
    int result = check_extension(filepath);
    EXPECT_EQ(result, -1);
}

TEST(validate_file, extension_at_the_end) {
    char *filepath = "testfile.rt.";
    int result = check_extension(filepath);
    EXPECT_EQ(result, -1);
}

TEST(validate_file, doubledot) {
    char *filepath = "test..rt";
    int result = check_extension(filepath);
    EXPECT_EQ(result, -1);
}

TEST(validate_file, no_extension) {
    char *filepath = "testfile";
    int result = check_extension(filepath);
    EXPECT_EQ(result, -1);
}

TEST(validate_file, hidden_file_with_valid_extension) {
    char *filepath = ".testfile.rt";
    int result = check_extension(filepath);
    EXPECT_EQ(result, 0);
}

TEST(validate_file, hidden_file_without_extension) {
    char *filepath = ".testfile";
    int result = check_extension(filepath);
    EXPECT_EQ(result, -1);
}

TEST(validate_file, valid_extension_with_uppercase) {
    char *filepath = "testfile.RT";
    int result = check_extension(filepath);
    EXPECT_EQ(result, -1);
}

TEST(validate_file, long_filename_with_valid_extension) {
    char *filepath = "averylongfilenamefortestingpurposes.rt";
    int result = check_extension(filepath);
    EXPECT_EQ(result, 0);
}

TEST(validate_file, special_characters_in_filename) {
    char *filepath = "test$file@!.rt";
    int result = check_extension(filepath);
    EXPECT_EQ(result, 0);
}

TEST(validate_file, special_characters_without_extension) {
    char *filepath = "test$file@!";
    int result = check_extension(filepath);
    EXPECT_EQ(result, -1);
}

TEST(validate_file, spaces_in_filename_valid_extension) {
    char *filepath = "test file.rt";
    int result = check_extension(filepath);
    EXPECT_EQ(result, 0);
}

TEST(validate_file, spaces_in_filename_invalid_extension) {
    char *filepath = "test file.txt";
    int result = check_extension(filepath);
    EXPECT_EQ(result, -1);
}

TEST(validate_file, extension_with_extra_period) {
    char *filepath = "testfile.rt.";
    int result = check_extension(filepath);
    EXPECT_EQ(result, -1);
}

TEST(validate_file, extension_with_trailing_spaces) {
    char *filepath = "testfile.rt   ";
    int result = check_extension(filepath);
    EXPECT_EQ(result, -1);
}

TEST(validate_file, valid_extension_with_leading_spaces) {
    char *filepath = "   testfile.rt";
    int result = check_extension(filepath);
    EXPECT_EQ(result, 0);
}

TEST(validate_file, numeric_filename_with_valid_extension) {
    char *filepath = "123456.rt";
    int result = check_extension(filepath);
    EXPECT_EQ(result, 0);
}

TEST(validate_file, numeric_filename_without_extension) {
    char *filepath = "123456";
    int result = check_extension(filepath);
    EXPECT_EQ(result, -1);
}

TEST(validate_file, very_large_filename) {
    char filepath[300];
    memset(filepath, 'a', 295);
    strcpy(filepath + 295, ".rt");
    int result = check_extension(filepath);
    EXPECT_EQ(result, 0);
}

TEST(validate_file, null_character_in_filename) {
    char filepath[] = "testfile.rt\0hidden.txt";
    int result = check_extension(filepath);
    EXPECT_EQ(result, 0);
}

