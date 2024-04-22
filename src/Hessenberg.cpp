#include "Hessenberg.hpp"

Hessenberg::Hessenberg(const CSR& A, const std::vector<double>& r0) {
    this->A = A;
    this->r0 = r0;
    this->n = A.getRowsSize();
    this->s = 0;

    V.push_back(r0 * (1 / mod(r0)));
}

void Hessenberg::step() {
    std::vector<double> t = A * V[s];
    H = H.change_size(s + 2, s + 1);

    double h;
    for (size_t k = 0; k < s + 1; k++) {
        h = V[k] * t;
        t = t - V[k] * h;
        H.at(k, s) = h; 
    }

    h = mod(t);
    V.push_back(t * (1 / h));
    H.at(s + 1, s) = h;

    Dense r = givens(H.get_column(s), s);
    rotation = r * rotation;
    H = r * H;

    s++;
}