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

Dense givens(const std::vector<double>& vec, unsigned int pos) {
    unsigned n = vec.size();
    Dense rot(std::vector<double>(n * n), n, n);
    Dense rot_tmp;
    double x = vec[pos], x_tmp;
    double co, si;

    for (unsigned int i = 0; i < n; ++i) {
        rot.at(i, i) = 1;
    }

    for (unsigned int i = pos + 1; i < n; ++i) {
        x_tmp = sqrt(x * x + vec[i] * vec[i]);
        co =  x / x_tmp;
        si = -vec[i] / x_tmp;
        x = x_tmp;

        rot_tmp = Dense(std::vector<double>(n * n), n, n);
        for (unsigned int i = 0; i < n; ++i) {
            rot_tmp.at(i, i) = 1;
        }
        rot_tmp.at(pos, pos) = co;
        rot_tmp.at(i, i) = co;
        rot_tmp.at(i, pos) = si;
        rot_tmp.at(pos, i) = -si;
        rot = rot_tmp * rot;
    }
    
    return rot;
}