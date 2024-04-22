#pragma once

#include <vector>
#include <cmath>
#include <iostream>

class Dense {
    public:
        Dense();
        Dense(const std::vector<double>& vector, unsigned int row, unsigned int col);

        double operator()(unsigned int i, unsigned int j) const;
        double& at(unsigned int i, unsigned int j);
        Dense operator+(const Dense& other) const;
        Dense operator*(const Dense& other) const;
        bool operator==(const Dense& other) const;
        Dense trans() const;
        std::vector<double> getData() const;
        std::vector<double> operator*(const std::vector<double>& other) const;
        std::size_t getRows() const;
        std::size_t getCols() const;
        Dense change_size(unsigned int new_row, unsigned int new_col) const;
        std::vector<double> get_column(unsigned int pos) const;

    private:
        unsigned int row, col;
        std::vector<double> vector;
};
