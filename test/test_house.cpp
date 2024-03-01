#include <gtest/gtest.h>

#include "householder.hpp"

TEST(house, qr) {
    Dense A = Dense({1, 2, 3, 4, 5, 5, 7, 8, 9}, 3, 3);

    householder HH = householder(A);

    EXPECT_TRUE(A == HH.getQ() * HH.getR());
}

TEST(house, x) {
    Dense A = Dense({1, 3, 4, 5, 3, 2, 2, 6, 1}, 3, 3);
    std::vector<double> x0 = {1, 1, 1};
    std::vector<double> b = A * x0;

    householder HH = householder(A);
    std::vector<double> x = HH.solveFor(b);
    
    std::cout << x[0] << std::endl << x[1] << std::endl << x[2] << std::endl;

    EXPECT_TRUE(x0 == x);
}