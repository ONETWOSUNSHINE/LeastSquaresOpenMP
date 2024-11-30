#include "poly_fit.h"
#include <cmath>
#include <omp.h>

double fillMatrix(const std::vector<double>& x, const std::vector<double>& y, std::vector<std::vector<double>>& A, std::vector<double>& b, int degree) {
    const int n = x.size();
    double t = omp_get_wtime();
    #pragma omp parallel
    {
        #pragma omp for collapse(2) schedule(static)
        for (int i = 0; i <= degree; ++i) {
            for (int j = 0; j <= degree; ++j) {
                for (int k = 0; k < n; ++k) {
                    A[i][j] += pow(x[k], i + j);
                }
            }
        }

        #pragma omp for schedule(static)
        for (int i = 0; i <= degree; ++i) {
            for (int k = 0; k < n; ++k) {
                b[i] += y[k] * pow(x[k], i);
            }
        }
    }
    t = omp_get_wtime() - t;
    return t;
}
