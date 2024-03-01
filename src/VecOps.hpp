#pragma once

#include <vector>
#include <cmath>

std::vector<double> operator+(const std::vector<double>& any, const std::vector<double>& other);
std::vector<double> operator-(const std::vector<double>& any, const std::vector<double>& other);
bool operator==(const std::vector<double>& any, const std::vector<double>& other);

double operator*(const std::vector<double>& any, const std::vector<double>& other);

double mod(const std::vector<double>& v);

std::vector<double> operator*(const std::vector<double>& any, double x);