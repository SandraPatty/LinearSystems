#include "SolveMethods.hpp"

std::vector<double> MPIMethod(const CSR& A, const std::vector<double>& b, double tau, double stop) {
    std::vector<double> x0(b.size()), x(b.size());
    std::vector<double> ostatok = A * x0 - b;
    while (stop < mod(ostatok)) { 
        x = x - ostatok * tau;
        ostatok = A * x - b;  
    }
    return x;
}

std::vector<double> JacobiMethod(const CSR& A, const std::vector<double>& b, double stop) {
    std::vector<double> x0(b.size()), x(b.size());
    CSR d = inverseJ(A);
    std::vector<double> ostatok = A * x - b;
    while (stop < mod(ostatok)) {
        x = d * (b - multiplyJ(A, x));
        ostatok = A * x - b;
    }
    return x;
}

std::vector<double> GaussSeidelMethod(const CSR& A, const std::vector<double>& b, double stop) {
    std::vector<double> x0(b.size()), x(b.size());
    std::vector<double> d = inverseGS(A);
    std::vector<double> ostatok = A * x - b;
    double tmp;
    while (stop < mod(ostatok)) {
        for (unsigned i = 0; i < x.size(); i++) {
            tmp = 0;
            for (unsigned j = A._rows(i); j < A._rows(i + 1); j++) {
                if (i != A._cols(j)) {
                    tmp += A._vals(j) * x[A._cols(j)];
                }
            }
            x[i] = d[i] * (b[i] - tmp);
        }
        ostatok = A * x - b;
    }
    return x;
}

std::vector<double> multiplyJ(const CSR& csr, const std::vector<double>& v) {
    std::vector<double> res(v.size());
    for (unsigned i = 0; i < v.size(); i++) {
        for (unsigned j = csr._rows(i); j < csr._rows(i + 1); j++) {
            if (i != csr._cols(j)) {
                res[i] += csr._vals(j) * v[csr._cols(j)];
            }
        }
    }
    return res;
}

CSR inverseJ(const CSR& csr) {
    unsigned n = csr.getRowsSize() - 1;
    std::vector<double> vals(n);
    std::vector<unsigned> cols(n), rows(n + 1);

    for (unsigned i = 0; i < n; i++) {
        for (unsigned j = csr._rows(i); j < csr._rows(i + 1); j++) {
            if (i == csr._cols(j)) {
                vals[i] = 1 / csr._vals(j);
                cols[i] = i;
                rows[i + 1] = i + 1;
            }
        }
    }

    return CSR(vals, cols, rows);
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
