#include <gtest/gtest.h>

#include "householder.hpp"

TEST(house, house1) {
    Dense A = Dense({1, 2, 3, 4, 5, 5, 7, 8, 9}, 3, 3);

    householder HH = householder(A);

    EXPECT_TRUE(A == HH.getQ() * HH.getR());
}