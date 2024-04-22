#include "Dense.hpp"

Dense::Dense() {}

Dense::Dense(const std::vector<double>& vector, unsigned int row, unsigned int col) {
    this->row = row;
    this->col = col;
    this->vector = vector;
}

double Dense::operator()(unsigned int i, unsigned int j) const {
    return vector[i * col + j];
}

double& Dense::at(unsigned int i, unsigned int j) {
    return vector[i * col + j];
}


Dense Dense::operator+(const Dense& other) const {
    std::vector<double> sum;
    for (unsigned int i = 0; i < row; i++) {
        for (unsigned int j = 0; j < col; j++) {
            sum.push_back(other(i, j) + vector[i * col + j]);
        }
    }
    return Dense(sum, row, col);
}

Dense Dense::operator*(const Dense& other) const {
    std::vector<double> product(row * other.col);
    for (unsigned int i = 0; i < row; i++) {
        for (unsigned int j = 0; j < other.col; j++) {
            for (unsigned int k = 0; k < col; k++) {
                product[i * col + j] += (*this)(i, k) * other(k, j);
            }
        }
    }
    return Dense(product, row, other.col);
}

std::vector<double> Dense::operator*(const std::vector<double>& other) const{
    std::vector<double> res(row);
    for (unsigned int i = 0; i < row; i++) {
        for (unsigned int j = 0; j < col; j++) {
            res[i] += (*this)(i, j) * other[j];
        }

    }
    return res;
}

bool Dense::operator==(const Dense& other) const {
    double precision = 1e-7;
    for (std::size_t i = 0; i < row; i++) {
        for (std::size_t j = 0; j < col; j++) {
            if (fabs((*this)(i, j) - other(i, j)) > precision) {
                return false;
            }       
        }
    }
    return true;
}

Dense Dense::trans() const {
    std::vector<double> Datanew(row *col);
    for (unsigned i = 0; i < row; i++) {
        for (unsigned j = 0; j < col; j++) {
            Datanew[row * j + i] = (*this)(i, j);
        }
    }
    return Dense(Datanew, row, col);
}

std::vector<double> Dense::getData() const{
    return vector;
}

std::size_t Dense::getRows() const {
    return row;
}

std::size_t Dense::getCols() const {
    return col;
}

Dense Dense::change_size(unsigned int new_row, unsigned int new_col) const {
    std::vector<double> new_matrix(new_row * new_col);
    for (size_t i = 0; i < new_row; ++i) {
        for (size_t j = 0; j < new_col; ++j) {
            new_matrix[new_row * i + j] = (*this)(i, j);
        }
    }
    return Dense(new_matrix, new_row, new_col);
}

std::vector<double> Dense::get_column(unsigned int pos) const {
    std::vector<double> res(row);
    for (size_t i = 0; i < row; i++) {
        res[i] = (*this)(i, pos);
    }
    return res;
}
