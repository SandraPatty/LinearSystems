#include "CSR.hpp"
#include "SolveMethods.hpp"
#include "VecOps.hpp"

#include <iostream>
#include <fstream>
#include <chrono>

CSR DiagDom(unsigned n) {
    std::vector<double> vals(n, 1);
    std::vector<unsigned> cols(n), rows(n + 1);
    for (unsigned i = 0; i < n; i++) {
        cols[i] = i;
        rows[i] = i;
    }
    rows[n] = n;

    return CSR(vals, cols, rows);
}


int main() {
    CSR A;
    std::vector<double> b;

    std::ofstream file1("../test/1.txt", std::ios::out);
    std::ofstream file2("../test/2.txt", std::ios::out);
    std::ofstream file3("../test/3.txt", std::ios::out);
    std::ofstream file4("../test/4.txt", std::ios::out);

    for (unsigned n = 0; n <= 500; n += 10) {
        A = DiagDom(n);
        std::vector<double> x_real(n, 1);
        b = A * x_real;

        std::vector<double> x_calc(n);

        auto start = std::chrono::high_resolution_clock::now(); 
        x_calc = MPIMethod(A, b, 0.1, 1e-7);
        auto end = std::chrono::high_resolution_clock::now();
        auto nsec = end - start;
        file1 << n << ' ' << nsec.count() << std::endl;
    
        start = std::chrono::high_resolution_clock::now(); 
        x_calc = JacobiMethod(A, b, 1e-7);
        end = std::chrono::high_resolution_clock::now();
        nsec = end - start;
        file2 << n << ' ' << nsec.count() << std::endl;

        start = std::chrono::high_resolution_clock::now(); 
        x_calc = GaussSeidelMethod(A, b, 1e-7);
        end = std::chrono::high_resolution_clock::now();
        nsec = end - start;
        file3 << n << ' ' << nsec.count() << std::endl;

        start = std::chrono::high_resolution_clock::now(); 
        x_calc = AccelGZ(A, b, 1e-7);
        end = std::chrono::high_resolution_clock::now();
        nsec = end - start;
        file4 << n << ' ' << nsec.count() << std::endl;
    }

    return 0;
}