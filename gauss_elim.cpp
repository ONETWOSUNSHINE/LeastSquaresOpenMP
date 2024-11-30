#include <omp.h>
#include "gauss_elim.h"
#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>


double gaussElim(std::vector<std::vector<double>>& A, std::vector<double>& b, std::vector<double>& x) {

    double s;
    const int n = A.size();
    double t = omp_get_wtime();

    #pragma omp parallel
    {
        for (int k = 0; k < n - 1; k++) {
            double diag = A[k][k];
            #pragma omp for schedule(static)
            for (int i = k + 1; i < n; i++) {
                double fact = A[i][k] / diag;
                for (int j = k; j < n; j++)
                    A[i][j] -= fact * A[k][j];
                b[i] -= fact * b[k];
            }
        }
        for (int k = n - 1; k >= 0; k--) {
            s = 0;
            #pragma omp barrier
            #pragma omp for reduction(+:s)
            for (int i = k + 1; i < n; i++)
                s += A[k][i] * x[i];
            #pragma omp single
            x[k] = (b[k] - s) / A[k][k];
            
        }
    }
    t = omp_get_wtime() - t;
    return t;

}


