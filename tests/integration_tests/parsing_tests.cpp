#include <gtest/gtest.h>
#include <cstdlib>
#include <cstring>

extern "C" {
    #include "../../inc/parser.h"
}

TEST(ParsingValidation, ValidFile1)
{
    char *filepath = ft_strdup("../testfiles/valid.rt");
    t_object **objs = NULL;

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
    EXPECT_EQ(objs[0]->colors[0], 255);
    EXPECT_EQ(objs[0]->colors[1], 255);
    EXPECT_EQ(objs[0]->colors[2], 255);

    // camera
    EXPECT_EQ(objs[1]->id[0], 'C');
    EXPECT_FLOAT_EQ(objs[1]->cords[0], -50.0);
    EXPECT_FLOAT_EQ(objs[1]->cords[1], 0.0);
    EXPECT_FLOAT_EQ(objs[1]->cords[2], 20.0);
    EXPECT_FLOAT_EQ(objs[1]->orientation_vector[0], 0);
    EXPECT_FLOAT_EQ(objs[1]->orientation_vector[1], 0);
    EXPECT_FLOAT_EQ(objs[1]->orientation_vector[2], 1);
    EXPECT_EQ(objs[1]->fov, 70);

    // light
    EXPECT_EQ(objs[2]->id[0], 'L');
    EXPECT_FLOAT_EQ(objs[2]->cords[0], -40.0);
    EXPECT_FLOAT_EQ(objs[2]->cords[1], 0.0);
    EXPECT_FLOAT_EQ(objs[2]->cords[2], 30.0);
    EXPECT_FLOAT_EQ(objs[2]->brightness, 0.7);
    EXPECT_EQ(objs[2]->colors[0], 255);
    EXPECT_EQ(objs[2]->colors[1], 255);
    EXPECT_EQ(objs[2]->colors[2], 255);

    free_objects(objs, no_elems);
    free(filepath);
}