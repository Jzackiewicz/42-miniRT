#include <gtest/gtest.h>
#include <cstdlib>
#include <cstring>

extern "C" {
    #include "../../inc/parser.h"  // Assuming this header contains the updated validate_file function
}

// TEST(FileValidationTest, ValidFile1) {
//     char *filepath = strdup("../testfiles/valid.rt");
//     int v = validate_file(filepath);
//     free(filepath);
//     EXPECT_EQ(v, 0);
// }

// TEST(FileValidationTest, ValidFile2) {
//     char *filepath = strdup("../testfiles/nls_between.rt");
//     int v = validate_file(filepath);
//     free(filepath);
//     EXPECT_EQ(v, 0);
// }

// TEST(FileValidationTest, ValidFile3) {
//     char *filepath = strdup("../testfiles/extra_nls.rt");
//     int v = validate_file(filepath);
//     EXPECT_EQ(v, 0);
//     free(filepath);
// }

// TEST(FileValidationTest, ValidFile4) {
//     char *filepath = strdup("../testfiles/multip_spaces.rt");
//     int v = validate_file(filepath);
//     EXPECT_EQ(v, 0);
//     free(filepath);
// }

// TEST(FileValidationTest, InvalidFile1) {
//     char *filepath = strdup("../testfiles/missing_plane_coords.rt");
//     int v = validate_file(filepath);
//     EXPECT_EQ(v, -1);
//     free(filepath);
// }

// TEST(FileValidationTest, InvalidFile2) {
//     char *filepath = strdup("../testfiles/missing_id.rt");
//     int v = validate_file(filepath);
//     EXPECT_EQ(v, -1);
//     free(filepath);
// }

// TEST(FileValidationTest, InvalidFile3) {
//     char *filepath = strdup("../testfiles/missing_field.rt");
//     int v = validate_file(filepath);
//     EXPECT_EQ(v, -1);
//     free(filepath);
// }

// TEST(FileValidationTest, InvalidFile4) {
//     char *filepath = strdup("../testfiles/missing_color.rt");
//     int v = validate_file(filepath);
//     EXPECT_EQ(v, -1);
//     free(filepath);
// }

// TEST(FileValidationTest, InvalidFile5) {
//     char *filepath = strdup("../testfiles/inv_vector_light.rt");
//     int v = validate_file(filepath);
//     EXPECT_EQ(v, -1);
//     free(filepath);
// }

// TEST(FileValidationTest, InvalidFile6) {
//     char *filepath = strdup("../testfiles/inv_vec.rt");
//     int v = validate_file(filepath);
//     EXPECT_EQ(v, -1);
//     free(filepath);
// }

// TEST(FileValidationTest, InvalidFile7) {
//     char *filepath = strdup("../testfiles/extra_char_light.rt");
//     int v = validate_file(filepath);
//     EXPECT_EQ(v, -1);
//     free(filepath);
// }

// TEST(FileValidationTest, InvalidFile8) {
//     char *filepath = strdup("../testfiles/extra_params_cylinder.rt");
//     int v = validate_file(filepath);
//     EXPECT_EQ(v, -1);
//     free(filepath);
// }

// TEST(FileValidationTest, InvalidFile9) {
//     char *filepath = strdup("../testfiles/inv_field_camera.rt");
//     int v = validate_file(filepath);
//     EXPECT_EQ(v, -1);
//     free(filepath);
// }

// TEST(FileValidationTest, InvalidFile10) {
//     char *filepath = strdup("../testfiles/inv_range_diam.rt");
//     int v = validate_file(filepath);
//     EXPECT_EQ(v, -1);
//     free(filepath);
// }


