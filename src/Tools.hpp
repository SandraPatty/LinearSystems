#pragma once

#include <vector>
#include "Dense.hpp"
#include "CSR.hpp"
#include "VecOps.hpp"
#include <cmath>

std::vector<double> GZs(const CSR& A, const std::vector<double>& b, const std::vector<double>& _x);

std::vector<double> inverseGS(const CSR& csr);