#pragma once

#include <vector>
#include "Dense.hpp"
#include "CSR.hpp"
#include "VecOps.hpp"
#include "Tools.hpp"

class Hessenberg {
    public:
    Hessenberg(const CSR& A, const std::vector<double>& r0);
    void step();

    private:
    unsigned n, s;

    CSR A;
    std::vector<double> r0;

    Dense rotation, H;
    std::vector<std::vector<double>> V;
};
