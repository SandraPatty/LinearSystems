#include <gtest/gtest.h>
#include "CSR.hpp"

TEST(csr, test1) {
    CSR a = CSR({1, 2, 4, 2, 6},
                {0, 0, 0, 0, 0},
                {0, 1, 2, 3, 4, 5});
    CSR b = CSR({3, 5, 2},
                {0, 0, 0},
                {0, 0, 1, 2, 2, 3});
    CSR c = a + b;
    std::vector<double> true_sum = {1, 5, 9, 2, 8};

    for (unsigned int i = 0; i < 5; i++) {
        ASSERT_NEAR(c(i, 0), true_sum[i], 1e-15);
    }
}