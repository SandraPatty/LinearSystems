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

std::vector<double> Chebyshev(const CSR& A, const std::vector<double>& b, double lmin, double lmax, unsigned n, double stop) {
    std::vector<double> x0(b.size()), x(b.size());
    std::vector<double> ostatok = A * x - b;
    std::vector<double> roots = ChebRoots(n);
    std::vector<size_t> trans = ChebTrans(n);
    while (stop < mod(ostatok)) { 
        for (size_t i = 0; i < n; i++) {
            double tau = 2 / (lmax + lmin + (lmax - lmin) * roots[trans[i]]);
            x = x - ostatok * tau;
            ostatok = A * x - b;
        }
    }
    return x;
}

std::vector<double> ChebRoots(unsigned n) {
    double sin1 = sin(M_PI / 2 / n);
    double cos1 = cos(M_PI / 2 / n);
    double sin2 = sin(M_PI / n);
    double cos2 = cos(M_PI / n);
    std::vector<double> roots(n);
    double tmp = sin1;
    roots[0] = cos2;
    for (size_t i = 1; i < n; i++) {
        roots[i] = roots[i - 1] * cos2 - tmp * sin2;
        tmp = tmp * cos2 + roots[i - 1] * sin2;
    }
    return roots;
}

std::vector<size_t> ChebTrans(unsigned n) {
    std::vector<size_t> trans(n);
    unsigned lg = log2(n);
    size_t tmp = n;
    for (size_t i = 0; i < lg; i++) {
        for (size_t j = 0; j < n; j += tmp) {
            trans[j + tmp / 2] = n / (tmp / 2) - 1 - trans[j];
        }
        tmp = tmp / 2;
    }
    return trans;
}
