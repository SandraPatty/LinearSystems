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

std::vector<double> CSR::operator*(const std::vector<double>& v) {
    std::vector<double> res(v.size());
    for (int i = 0; i < v.size(); ++i) {
        for (int k = rows[i]; k < rows[i + 1]; ++k) {
            res[i] += values[k] * v[cols[k]];
        }
    }
    return res;
}

double CSR::operator*(const CSR& other) const {
    double res = 0;
    for (unsigned i = 1; i < rows.size(); i++) {
        if ((rows[i] == rows[i - 1] + 1) && (other.rows[i] == other.rows[i - 1]) + 1) {
            res += values[rows[i - 1]] * other.values[other.rows[i - 1]];
        }
    }
    return res;
}

  CSR CSR::operator+(const CSR& other) const {

        CSR result;
        result.rows = this->rows;
        for (unsigned int i = 1; i < rows.size(); i++) {
            unsigned int n = (this->rows[i] - this->rows[i-1]);
            unsigned int m = (other.rows[i] - other.rows[i-1]);
            if(n || m) {
                result.cols.push_back(0);
                result.rows[i] = result.rows[i-1]+1;
                result.values.push_back(values[this->rows[i - 1]] * n + other.values[other.rows[i - 1]] * m);             } 
            else {
                result.rows[i] = result.rows[i-1];
            }
        }

        return result;
    }