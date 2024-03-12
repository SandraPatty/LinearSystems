#include <gtest/gtest.h>

#include "CSR.hpp"
#include "VecOps.hpp"
#include "SolveMethods.hpp"

TEST(fixedPointIteration, main) {
    CSR A = CSR({2, 1, 5, 4, 3}, {0, 1, 1, 0, 2}, {0, 2, 3, 5});
	std::vector<double> x_real = {1, 1, 1}, x_calc;
    std::vector<double> b = A * x_real;
    x_calc = MPIMethod(A, b, 0.1, 1e-13);
    EXPECT_TRUE(x_calc == x_real);
}

TEST(Jacobi, main) {
    CSR A = CSR({2, 1, 5, 4, 3}, {0, 1, 1, 0, 2}, {0, 2, 3, 5});
	std::vector<double> x_real = {1, 1, 1}, x_calc;
    std::vector<double> b = A * x_real;
    x_calc = JacobiMethod(A, b, 1e-7);
    EXPECT_TRUE(x_calc == x_real);
}

TEST(GaussSeidel, main) {
    CSR A = CSR({2, 1, 5, 4, 3}, {0, 1, 1, 0, 2}, {0, 2, 3, 5});
	std::vector<double> x_real = {1, 1, 1}, x_calc;
    std::vector<double> b = A * x_real;
    x_calc = GaussSeidelMethod(A, b, 1e-7);
    EXPECT_TRUE(x_calc == x_real);
}

TEST(Chebyshev, main) {
    CSR A = CSR({2, 1, 5, 4, 3}, {0, 1, 1, 0, 2}, {0, 2, 3, 5});
	std::vector<double> x_real = {1, 1, 1}, x_calc;
    std::vector<double> b = A * x_real;
    x_calc = Chebyshev(A, b, 2, 5, 8, 1e-7);
    EXPECT_TRUE(x_calc == x_real);
}