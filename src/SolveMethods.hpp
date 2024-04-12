#pragma once

#include "Dense.hpp"
#include "Tools.hpp"
#include "CSR.hpp"
#include "VecOps.hpp"

std::vector<double> MPIMethod(const CSR& A, const std::vector<double>& b, double tau, double stop);
std::vector<double> JacobiMethod(const CSR& A, const std::vector<double>& b, double stop);
std::vector<double> GaussSeidelMethod(const CSR& A, const std::vector<double>& b, double stop);
std::vector<double> SteepDescent(const CSR& A, const std::vector<double>& b, double stop);
std::vector<double> SymmetryGZ(const CSR& A, const std::vector<double>& b, double stop);
std::vector<double> AccelGZ(const CSR& A, const std::vector<double>& b, double stop);
std::vector<double> ConjGrad(const CSR& A, const std::vector<double>& b, double stop);

std::vector<double> multiplyJ(const CSR& csr, const std::vector<double>& v);
CSR inverseJ(const CSR& csr);
std::vector<double> inverseGS(const CSR& csr);

std::vector<double> Chebyshev(const CSR& A, const std::vector<double>& b, double lmin, double lmax, unsigned n, double stop);
std::vector<double> ChebRoots(unsigned n);
std::vector<size_t> ChebTrans(unsigned n);
