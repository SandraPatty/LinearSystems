#include "CSR.hpp"

CSR::CSR() {}

CSR::CSR(const std::vector<double>& values, const std::vector<unsigned int>& cols, const std::vector<unsigned int>& rows) {
    this->values = values;
    this->cols = cols;
    this->rows = rows;
}

double CSR::operator()(unsigned int i, unsigned int j) const {
    for (int k = rows[i]; k < rows[i + 1]; k++) {
        if (cols[k] == j) {
            return values[k];
        }
    }
    return 0;
}

std::vector<double> CSR::operator*(const std::vector<double>& v) const {
    std::vector<double> res(v.size());
    for (int i = 0; i < v.size(); ++i) {
        for (int k = rows[i]; k < rows[i + 1]; ++k) {
            res[i] += values[k] * v[cols[k]];
        }
    }
    return res;
}

size_t CSR::getRowsSize() const {
    return rows.size();
}

double CSR::_vals(std::size_t i) const {
    return values[i];
}

unsigned int CSR::_cols(std::size_t i) const {
    return cols[i];
}

unsigned int CSR::_rows(std::size_t i) const {
    return rows[i];
}
