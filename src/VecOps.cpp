#include "VecOps.hpp"

std::vector<double> operator+(const std::vector<double> &any, const std::vector<double> &other)
{
    std::size_t n = any.size();
    std::vector<double> res(n);
    for (std::size_t i = 0; i < n; i++)
    {
        res[i] = any[i] + other[i];
    }
    return res;
}

std::vector<double> operator-(const std::vector<double>& any, const std::vector<double>& other) {
    std::size_t n = any.size();
    std::vector<double> res(n);
    res = any + other * (-1);
    return res;
}

double operator*(const std::vector<double> &any, const std::vector<double> &other)
{
    std::size_t n = any.size();
    double res = 0;
    for (std::size_t i = 0; i < n; i++)
    {
        res += any[i] * other[i];
    }
    return res;
}

double mod(const std::vector<double>& v) {
    std::size_t n = v.size();
    double res = 0;
    for (std::size_t i = 0; i < n; i++)
    {
        res += v[i] * v[i];
    }
    return sqrt(res);
}

std::vector<double> operator*(const std::vector<double>& any, double x) {
    std::size_t n = any.size();
    std::vector<double> res(n);
    for (std::size_t i = 0; i < n; i++)
    {
        res[i] = any[i] * x;
    }
    return res;
}