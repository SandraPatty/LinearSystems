#include "householder.hpp"

householder::householder(const Dense &A)
{
    std::size_t n = A.getRows();
    std::vector<double> e(n), x(n);
    std::vector<double> data = A.trans().getData();
    std::vector<double> dataE(n * n);

    for (std::size_t i = 0; i < n; i++)
    {
        dataE[i * n + i] = 1;
    }

    for (std::size_t i = 0; i < n - 1; i++)
    {
        e[i] = 1;
        x = A * e;
        std::vector<double> es = std::vector<double>(e.begin() + i, e.begin() + n);
        std::vector<double> xs = std::vector<double>(x.begin() + i, x.begin() + n);
        std::vector<double> v;
        if (xs[0] >= 0)
        {
            v = xs + es * mod(xs);
        }
        else
        {
            v = xs - es * mod(xs);
        }

        for (std::size_t j = i; j < n; j++)
        {
            std::vector xsl = std::vector<double>(data.begin() + j * n + i, data.begin() + (j + 1) * n);
            xsl = theta(xsl, v);
            for (std::size_t k = 0; k < n - i; k++)
            {
                data[j * n + i + k] = xsl[k];
            }
        }

        for (std::size_t j = 0; j < n; j++)
        {
            std::vector xsl = std::vector<double>(dataE.begin() + j * n + i, dataE.begin() + (j + 1) * n);
            xsl = theta(xsl, v);
            for (std::size_t k = 0; k < n - i; k++)
            {
                dataE[j * n + i + k] = xsl[k];
            }
        }

        R = Dense(data, n, n).trans();
        Q = Dense(dataE, n, n);

        e[i] = 0;
    }
}

Dense householder::getQ() const
{
    return Q;
}

Dense householder::getR() const
{
    return R;
}

std::vector<double> householder::theta(const std::vector<double> &x, const std::vector<double> &v)
{
    std::size_t n = x.size();
    std::vector<double> res(n);
    res = x - v * (2 * (v * x) / (v * v));
    return res;
}

std::vector<double> householder::solveFor(const std::vector<double> &b) const
{
    std::vector<double> b1 = Q.trans() * b;
    std::size_t n = b.size();
    std::vector<double> x(n);
    double sum;
    for (int i = n - 1; i >= 0; i--) {
        sum = 0;
        for (unsigned j = n - 1; j > i; j--) {
            sum += R(i, j) * x[j];
        }
        x[i] = (b1[i] - sum) / R(i, i); 
    }
    return x;
}
