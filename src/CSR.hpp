#pragma once

#include <vector>
#include <iostream>

class CSR {
    public:
        CSR(const std::vector<double>& values, const std::vector<unsigned int>& cols, const std::vector<unsigned int>& rows);
        CSR();
        double operator()(unsigned int i, unsigned int j) const;
        CSR operator+(const CSR& other) const;
        std::vector<double> operator*(const std::vector<double>& v);
        double operator*(const CSR& other) const;

    protected:
        std::vector<double> values;
        std::vector<unsigned int> cols, rows;
};
