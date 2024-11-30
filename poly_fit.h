#ifndef POLY_FIT_H
#define POLY_FIT_H

#include <vector>

double fillMatrix(const std::vector<double>& x, const std::vector<double>& y, std::vector<std::vector<double>>& A, std::vector<double>& b, int degree);

#endif /* POLY_FIT_H */
