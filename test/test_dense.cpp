#include <gtest/gtest.h>
#include "Dense.hpp"

TEST(dense, test1) {
    Dense a = Dense({1, 2, 4, 2, 6}, 1, 5);
    Dense b = Dense({3, 5, 2, 1, 7}, 5, 1);
    double c = (a * b)(0, 0);
    double d = 65;
    ASSERT_NEAR(c, d, 1e-15);
}