#pragma once

#include <vector>
#include <iostream>

class Dense {
    public:
        Dense(const std::vector<double>& vector, unsigned int row, unsigned int col);

        double operator()(unsigned int i, unsigned int j) const;
        Dense operator+(const Dense& other) const;

    private:
        unsigned int row, col;
        std::vector<double> vector;
};
