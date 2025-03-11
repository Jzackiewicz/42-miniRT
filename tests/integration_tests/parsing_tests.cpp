#include <gtest/gtest.h>
#include <cstdlib>
#include <cstring>

extern "C" {
    #include "../../inc/parser.h"
}

TEST(ParsingValidation, ValidFile1)
{
    char *filepath = strdup("../testfiles/valid.rt");
    
}