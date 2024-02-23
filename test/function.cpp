#include <iostream>
#include <fstream>
#include <vector>
#include <span> 

void function(std::string name) {
    std::ifstream infile;
    infile.open("../" + name);

    int n;
    infile >> n;
    n--;

    std::vector<double> Data(7*n+5, 0);

    std::span A(Data.begin(), Data.begin() + (n + 1)),
    B(Data.begin() + 1*(n + 1), Data.begin() + 2*(n + 1)),
    C(Data.begin() + 2*(n + 1), Data.begin() + 3*(n + 1)),
    D(Data.begin() + 3*(n + 1), Data.begin() + 4*(n + 1)),
    P(Data.begin() + 4*(n + 1), Data.begin() + 5*(n + 1)),
    Q(Data.begin() + 5*(n + 1), Data.begin() + 6*(n + 1)), 
    X(Data.begin() + 6*(n + 1), Data.begin() + 7*(n + 1));

   //inwrite

    for (int i = 1; i < 3 * n - 1; i++){
        int a = i % 3;
        int b = i / 3;
        infile >> Data[n * a + b];
    }

    for (int i = 0; i < n; i++){
        infile >> Data[3 * n + i];
    }

    //solve
    for (int i = 0; i < n - 1; i++) {
	    P[i + 1] = -C[i] / (A[i] * P[i] + B[i]);
		Q[i + 1] = (D[i] - A[i] * Q[i]) / (A[i] * P[i] + B[i]);
	}

    X[n] = (D[n] - A[n] * Q[n]) / (A[n] * P[n] + B[n]);

    for (int i = n - 2; i >= 0; i--) {
		X[i] = P[i + 1] * X[i + 1] + Q[i + 1];
	}

    //output 
    for (int i = 0; i <=n; i++) {
	    std::cout << X[i] << std::endl;
	}
}
