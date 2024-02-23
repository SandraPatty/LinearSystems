#include "Dense.hpp"

Dense::Dense(const std::vector<double>& vector, unsigned int row, unsigned int col) {
    this->row = row;
    this->col = col;
    this->vector = vector;
}

double Dense::operator()(unsigned int i, unsigned int j) const {
    return vector[i * col + j];
}

Dense Dense::operator+(const Dense& other) const {
    std::vector<double> sum;
    for (unsigned int i = 0; i < row; i++) {
        for (unsigned int j = 0; j < col; j++) {
            sum.push_back(other(i, j) + vector[i * col + j]);
        }
    }
}
