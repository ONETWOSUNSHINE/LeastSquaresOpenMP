#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "gauss_elim.h"
#include "poly_fit.h"
#include "utils.h"
#include <omp.h>


int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage:\n " << argv[0] << " <input_file> [-pt]\n   -pt = Threads performance test (1-8)" << std::endl;
        return EXIT_FAILURE;
    }
    std::string inputData = argv[1];
    std::vector<double> x, y;
    int degree;
    bool perfTest = (argc > 2 && std::string(argv[2]) == "-pt");

    if (!readData(inputData, x, y, degree)) {
        std::cerr << "Can't open input file!" << std::endl;
        return EXIT_FAILURE;
    }

    std::vector<std::vector<double>> A(degree + 1, std::vector<double>(degree + 1, 0.0));
    std::vector<double> b(degree + 1, 0.0);

    double t1 = fillMatrix(x, y, A, b, degree);
    std::vector<double> coeffs(degree + 1, 0.0);
    double t2 = gaussElim(A, b, coeffs);
    double elapsedTime = t1 + t2;

    writeResultsToFile(coeffs, degree, elapsedTime, inputData);

    std::cout << "Coefficients of a polynomial of degree " << degree << ":\n";
    int i = 0;
    for (double coeff : coeffs) {
        std::cout << " x^" << i++ << ": " << coeff << std::endl;
    }
    std::cout << "Elapsed time (sec): "<< elapsedTime << std::endl;

    if (perfTest) 
        performanceTest(inputData, x, y, degree);
    


    return EXIT_SUCCESS;
}
