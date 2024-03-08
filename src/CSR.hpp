#pragma once

#include <vector>
#include <iostream>

class CSR {
    public:
        CSR(const std::vector<double>& values, const std::vector<unsigned int>& cols, const std::vector<unsigned int>& rows);
        CSR();
        double operator()(unsigned int i, unsigned int j) const;
        std::vector<double> operator*(const std::vector<double>& v) const;
        std::size_t getRowsSize() const;
        double _vals(std::size_t i) const;
        unsigned int _cols(std::size_t i) const;
        unsigned int _rows(std::size_t i) const;

    protected:
        std::vector<double> values;
        std::vector<unsigned int> cols, rows;
};
