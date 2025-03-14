#include <gtest/gtest.h>
#include <cstdlib>
#include <cstring>

extern "C" {
    #include "../../inc/parser.h"
}

TEST(ParsingValidation, ValidFile1)
{
    char *filepath = ft_strdup("../testfiles/valid.rt");
    t_input_data **objs = NULL;

    int no_elems = parse_file(filepath, &objs);

    ASSERT_NE(objs, nullptr);
    ASSERT_NE(objs[0], nullptr);
    ASSERT_NE(objs[1], nullptr);
    ASSERT_NE(objs[2], nullptr);
    ASSERT_NE(objs[3], nullptr);
    ASSERT_NE(objs[4], nullptr);
    ASSERT_NE(objs[5], nullptr);

    // ambient Light
    EXPECT_EQ(objs[0]->id[0], 'A');
    EXPECT_FLOAT_EQ(objs[0]->ambient_light_ratio, 0.2);
    EXPECT_EQ(objs[0]->color[0], 255);
    EXPECT_EQ(objs[0]->color[1], 255);
    EXPECT_EQ(objs[0]->color[2], 255);

    // camera
    EXPECT_EQ(objs[1]->id[0], 'C');
    EXPECT_FLOAT_EQ(objs[1]->coords[0], -50.0);
    EXPECT_FLOAT_EQ(objs[1]->coords[1], 0.0);
    EXPECT_FLOAT_EQ(objs[1]->coords[2], 20.0);
    EXPECT_FLOAT_EQ(objs[1]->orientation_vector[0], 0);
    EXPECT_FLOAT_EQ(objs[1]->orientation_vector[1], 0);
    EXPECT_FLOAT_EQ(objs[1]->orientation_vector[2], 1);
    EXPECT_EQ(objs[1]->fov, 70);

    // light
    EXPECT_EQ(objs[2]->id[0], 'L');
    EXPECT_FLOAT_EQ(objs[2]->coords[0], -40.0);
    EXPECT_FLOAT_EQ(objs[2]->coords[1], 0.0);
    EXPECT_FLOAT_EQ(objs[2]->coords[2], 30.0);
    EXPECT_FLOAT_EQ(objs[2]->brightness, 0.7);
    EXPECT_EQ(objs[2]->color[0], 255);
    EXPECT_EQ(objs[2]->color[1], 255);
    EXPECT_EQ(objs[2]->color[2], 255);

    // plane
    EXPECT_STREQ(objs[3]->id, "pl");
    EXPECT_FLOAT_EQ(objs[3]->coords[0], 0.0);
    EXPECT_FLOAT_EQ(objs[3]->coords[1], 0.0);
    EXPECT_FLOAT_EQ(objs[3]->coords[2], 0.0);
    EXPECT_FLOAT_EQ(objs[3]->vector[0], 0.0);
    EXPECT_FLOAT_EQ(objs[3]->vector[1], 1.0);
    EXPECT_FLOAT_EQ(objs[3]->vector[2], 0.0);
    EXPECT_EQ(objs[3]->color[0], 255);
    EXPECT_EQ(objs[3]->color[1], 0);
    EXPECT_EQ(objs[3]->color[2], 225);

    // sphere
    EXPECT_STREQ(objs[4]->id, "sp");
    EXPECT_FLOAT_EQ(objs[4]->coords[0], 0.0);
    EXPECT_FLOAT_EQ(objs[4]->coords[1], 0.0);
    EXPECT_FLOAT_EQ(objs[4]->coords[2], 20.0);
    EXPECT_FLOAT_EQ(objs[4]->diameter, 20.0);
    EXPECT_EQ(objs[4]->color[0], 255);
    EXPECT_EQ(objs[4]->color[1], 0);
    EXPECT_EQ(objs[4]->color[2], 0);

    // cylinder
    EXPECT_STREQ(objs[5]->id, "cy");
    EXPECT_FLOAT_EQ(objs[5]->coords[0], 50.0);
    EXPECT_FLOAT_EQ(objs[5]->coords[1], 0.0);
    EXPECT_FLOAT_EQ(objs[5]->coords[2], 20.6);
    EXPECT_FLOAT_EQ(objs[5]->vector[0], 0.0);
    EXPECT_FLOAT_EQ(objs[5]->vector[1], 0.0);
    EXPECT_FLOAT_EQ(objs[5]->vector[2], 1.0);
    EXPECT_FLOAT_EQ(objs[5]->diameter, 14.2);
    EXPECT_FLOAT_EQ(objs[5]->height, 21.42);
    EXPECT_EQ(objs[5]->color[0], 10);
    EXPECT_EQ(objs[5]->color[1], 0);
    EXPECT_EQ(objs[5]->color[2], 255);

    free_objects(objs, no_elems);
    free(filepath);
}

TEST(ParsingValidation, ValidFile2)
{
    char *filepath = ft_strdup("../testfiles/multip_spaces.rt");
    t_input_data **objs = NULL;

    int no_elems = parse_file(filepath, &objs);

    ASSERT_NE(objs, nullptr);
    ASSERT_NE(objs[0], nullptr);
    ASSERT_NE(objs[1], nullptr);
    ASSERT_NE(objs[2], nullptr);
    ASSERT_NE(objs[3], nullptr);
    ASSERT_NE(objs[4], nullptr);
    ASSERT_NE(objs[5], nullptr);

    // ambient Light
    EXPECT_EQ(objs[0]->id[0], 'A');
    EXPECT_FLOAT_EQ(objs[0]->ambient_light_ratio, 0.3);
    EXPECT_EQ(objs[0]->color[0], 255);
    EXPECT_EQ(objs[0]->color[1], 255);
    EXPECT_EQ(objs[0]->color[2], 255);

    // camera
    EXPECT_EQ(objs[1]->id[0], 'C');
    EXPECT_FLOAT_EQ(objs[1]->coords[0], -50.0);
    EXPECT_FLOAT_EQ(objs[1]->coords[1], 0.0);
    EXPECT_FLOAT_EQ(objs[1]->coords[2], 20.0);
    EXPECT_FLOAT_EQ(objs[1]->orientation_vector[0], 0);
    EXPECT_FLOAT_EQ(objs[1]->orientation_vector[1], 0);
    EXPECT_FLOAT_EQ(objs[1]->orientation_vector[2], 1);
    EXPECT_EQ(objs[1]->fov, 90);

    // light
    EXPECT_EQ(objs[2]->id[0], 'L');
    EXPECT_FLOAT_EQ(objs[2]->coords[0], -40.0);
    EXPECT_FLOAT_EQ(objs[2]->coords[1], 0.0);
    EXPECT_FLOAT_EQ(objs[2]->coords[2], 50.0);
    EXPECT_FLOAT_EQ(objs[2]->brightness, 0.5);
    EXPECT_EQ(objs[2]->color[0], 10);
    EXPECT_EQ(objs[2]->color[1], 10);
    EXPECT_EQ(objs[2]->color[2], 255);

    // plane
    EXPECT_STREQ(objs[3]->id, "pl");
    EXPECT_FLOAT_EQ(objs[3]->coords[0], 0.0);
    EXPECT_FLOAT_EQ(objs[3]->coords[1], 0.0);
    EXPECT_FLOAT_EQ(objs[3]->coords[2], 10.0);
    EXPECT_FLOAT_EQ(objs[3]->vector[0], 0.0);
    EXPECT_FLOAT_EQ(objs[3]->vector[1], 1.0);
    EXPECT_FLOAT_EQ(objs[3]->vector[2], 0.0);
    EXPECT_EQ(objs[3]->color[0], 255);
    EXPECT_EQ(objs[3]->color[1], 100);
    EXPECT_EQ(objs[3]->color[2], 0);

    // sphere
    EXPECT_STREQ(objs[4]->id, "sp");
    EXPECT_FLOAT_EQ(objs[4]->coords[0], 0.0);
    EXPECT_FLOAT_EQ(objs[4]->coords[1], 0.0);
    EXPECT_FLOAT_EQ(objs[4]->coords[2], 20.0);
    EXPECT_FLOAT_EQ(objs[4]->diameter, 15.0);
    EXPECT_EQ(objs[4]->color[0], 255);
    EXPECT_EQ(objs[4]->color[1], 0);
    EXPECT_EQ(objs[4]->color[2], 255);

    // cylinder
    EXPECT_STREQ(objs[5]->id, "cy");
    EXPECT_FLOAT_EQ(objs[5]->coords[0], 100.0);
    EXPECT_FLOAT_EQ(objs[5]->coords[1], 0.0);
    EXPECT_FLOAT_EQ(objs[5]->coords[2], 0.0);
    EXPECT_FLOAT_EQ(objs[5]->vector[0], 1.0);
    EXPECT_FLOAT_EQ(objs[5]->vector[1], 0.0);
    EXPECT_FLOAT_EQ(objs[5]->vector[2], 0.0);
    EXPECT_FLOAT_EQ(objs[5]->diameter, 12.0);
    EXPECT_FLOAT_EQ(objs[5]->height, 20.0);
    EXPECT_EQ(objs[5]->color[0], 0);
    EXPECT_EQ(objs[5]->color[1], 255);
    EXPECT_EQ(objs[5]->color[2], 0);

    free_objects(objs, no_elems);
    free(filepath);
}

TEST(ParsingValidation, MultipleObjectsFile)
{
    char *filepath = ft_strdup("../testfiles/multiple_objects.rt");
    t_input_data **objs = NULL;

    int no_elems = parse_file(filepath, &objs);

    ASSERT_NE(objs, nullptr);
    ASSERT_GE(no_elems, 6);

    // Ambient Light
    EXPECT_EQ(objs[0]->id[0], 'A');
    EXPECT_FLOAT_EQ(objs[0]->ambient_light_ratio, 0.3);
    EXPECT_EQ(objs[0]->color[0], 200);
    EXPECT_EQ(objs[0]->color[1], 200);
    EXPECT_EQ(objs[0]->color[2], 200);

    // Camera
    EXPECT_EQ(objs[1]->id[0], 'C');
    EXPECT_FLOAT_EQ(objs[1]->coords[0], 0.0);
    EXPECT_FLOAT_EQ(objs[1]->coords[1], 0.0);
    EXPECT_FLOAT_EQ(objs[1]->coords[2], 50.0);
    EXPECT_FLOAT_EQ(objs[1]->orientation_vector[0], 0.0);
    EXPECT_FLOAT_EQ(objs[1]->orientation_vector[1], 0.0);
    EXPECT_FLOAT_EQ(objs[1]->orientation_vector[2], -1.0);
    EXPECT_EQ(objs[1]->fov, 90);

    // Light
    EXPECT_EQ(objs[2]->id[0], 'L');
    EXPECT_FLOAT_EQ(objs[2]->coords[0], 10.0);
    EXPECT_FLOAT_EQ(objs[2]->coords[1], 20.0);
    EXPECT_FLOAT_EQ(objs[2]->coords[2], 30.0);
    EXPECT_FLOAT_EQ(objs[2]->brightness, 0.8);
    EXPECT_EQ(objs[2]->color[0], 255);
    EXPECT_EQ(objs[2]->color[1], 255);
    EXPECT_EQ(objs[2]->color[2], 255);

    // Plane
    EXPECT_STREQ(objs[3]->id, "pl");
    EXPECT_FLOAT_EQ(objs[3]->coords[0], 0.0);
    EXPECT_FLOAT_EQ(objs[3]->coords[1], -10.0);
    EXPECT_FLOAT_EQ(objs[3]->coords[2], 0.0);
    EXPECT_FLOAT_EQ(objs[3]->vector[0], 0.0);
    EXPECT_FLOAT_EQ(objs[3]->vector[1], 1.0);
    EXPECT_FLOAT_EQ(objs[3]->vector[2], 0.0);
    EXPECT_EQ(objs[3]->color[0], 100);
    EXPECT_EQ(objs[3]->color[1], 100);
    EXPECT_EQ(objs[3]->color[2], 100);

    // Sphere 1
    EXPECT_STREQ(objs[4]->id, "sp");
    EXPECT_FLOAT_EQ(objs[4]->coords[0], 10.0);
    EXPECT_FLOAT_EQ(objs[4]->coords[1], 10.0);
    EXPECT_FLOAT_EQ(objs[4]->coords[2], 20.0);
    EXPECT_FLOAT_EQ(objs[4]->diameter, 5.0);
    EXPECT_EQ(objs[4]->color[0], 0);
    EXPECT_EQ(objs[4]->color[1], 255);
    EXPECT_EQ(objs[4]->color[2], 0);

    // Sphere 2
    EXPECT_STREQ(objs[5]->id, "sp");
    EXPECT_FLOAT_EQ(objs[5]->coords[0], -10.0);
    EXPECT_FLOAT_EQ(objs[5]->coords[1], -10.0);
    EXPECT_FLOAT_EQ(objs[5]->coords[2], 15.0);
    EXPECT_FLOAT_EQ(objs[5]->diameter, 8.0);
    EXPECT_EQ(objs[5]->color[0], 255);
    EXPECT_EQ(objs[5]->color[1], 255);
    EXPECT_EQ(objs[5]->color[2], 0);

    // Cylinder 1
    EXPECT_STREQ(objs[6]->id, "cy");
    EXPECT_FLOAT_EQ(objs[6]->coords[0], 20.0);
    EXPECT_FLOAT_EQ(objs[6]->coords[1], 5.0);
    EXPECT_FLOAT_EQ(objs[6]->coords[2], 10.0);
    EXPECT_FLOAT_EQ(objs[6]->vector[0], 0.0);
    EXPECT_FLOAT_EQ(objs[6]->vector[1], 1.0);
    EXPECT_FLOAT_EQ(objs[6]->vector[2], 0.0);
    EXPECT_FLOAT_EQ(objs[6]->diameter, 5.0);
    EXPECT_FLOAT_EQ(objs[6]->height, 10.0);
    EXPECT_EQ(objs[6]->color[0], 0);
    EXPECT_EQ(objs[6]->color[1], 0);
    EXPECT_EQ(objs[6]->color[2], 255);

    // Cylinder 2
    EXPECT_STREQ(objs[7]->id, "cy");
    EXPECT_FLOAT_EQ(objs[7]->coords[0], -20.0);
    EXPECT_FLOAT_EQ(objs[7]->coords[1], -5.0);
    EXPECT_FLOAT_EQ(objs[7]->coords[2], 15.0);
    EXPECT_FLOAT_EQ(objs[7]->vector[0], 1.0);
    EXPECT_FLOAT_EQ(objs[7]->vector[1], 0.0);
    EXPECT_FLOAT_EQ(objs[7]->vector[2], 0.0);
    EXPECT_FLOAT_EQ(objs[7]->diameter, 3.0);
    EXPECT_FLOAT_EQ(objs[7]->height, 15.0);
    EXPECT_EQ(objs[7]->color[0], 255);
    EXPECT_EQ(objs[7]->color[1], 0);
    EXPECT_EQ(objs[7]->color[2], 0);

    free_objects(objs, no_elems);
    free(filepath);
}
