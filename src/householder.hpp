#pragma once

#include <vector>
#include <span>
#include <iostream>
#include "VecOps.hpp"
#include "Dense.hpp"

class householder {
    public:
        householder(const Dense& A);
        Dense getQ() const;
        Dense getR() const;
        std::vector<double> solveFor(const std::vector<double>& b) const;
    private:
        std::vector<double> theta(const std::vector<double>& x, const std::vector<double>& v);
        Dense Q, R;
};