#pragma once

#include <vector>
#include <span>
#include <iostream>
#include "VecOps.hpp"
#include "Dense.hpp"

class householder {
    public:
        householder(const Dense& A);
        Dense getQ();
        Dense getR();
    private:
        std::vector<double> theta(const std::vector<double>& x, const std::vector<double>& v);
        Dense Q, R;
};