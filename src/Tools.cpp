#include "Tools.hpp"

std::vector<double> GZs(const CSR& A, const std::vector<double>& b, const std::vector<double>& _x) {
    std::vector<double> x = _x;
    std::vector<double> d = inverseGS(A);
    double tmp;
    for (unsigned i = 0; i < x.size(); i++) {
        tmp = 0;
        for (unsigned j = A._rows(i); j < A._rows(i + 1); j++) {
            if (i != A._cols(j)) {
                tmp += A._vals(j) * x[A._cols(j)];
            }
        }
        x[i] = d[i] * (b[i] - tmp);
    }

    for (unsigned i = x.size() - 1; (i + 1) > 0; i--) {
        tmp = 0;
        for (unsigned j = A._rows(i); j < A._rows(i + 1); j++) {
            if (i != A._cols(j)) {
                tmp += A._vals(j) * x[A._cols(j)];
            }
        }
        x[i] = d[i] * (b[i] - tmp);
    }
    return x;

}


std::vector<double> inverseGS(const CSR& csr) {
    unsigned n = csr.getRowsSize() - 1;
    std::vector<double> res(n);

    for (unsigned i = 0; i < n; i++) {
        for (unsigned j = csr._rows(i); j < csr._rows(i + 1); j++) {
            if (i == csr._cols(j)) {
                res[i] = 1 / csr._vals(j);
            }
        }
    }

    return res;
}