#include "utils.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <omp.h>
#include "gauss_elim.h"
#include "poly_fit.h"


bool readData(const std::string& filename, std::vector<double>& x, std::vector<double>& y, int& degree) {
    std::ifstream file(filename);
    if (!file.is_open()) 
        return false;
    
    std::string line;
    std::getline(file, line); 
    degree = std::stoi(line);

    double xi, yi;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        if (iss >> xi >> yi) {
            x.push_back(xi);
            y.push_back(yi);
        }
    }

    return true;
}

bool writeResultsToFile(const std::vector<double>& coeffs, int degree, double elapsedTime, const std::string& fileName) {
    size_t pos = fileName.find(".txt");
    std::string inputDataTxtName = fileName;
    if (pos != std::string::npos) {
        inputDataTxtName = fileName.substr(0, pos);  
    }

    std::ofstream outFile(inputDataTxtName + "_results.txt");
    if (!outFile.is_open()) {
        std::cerr << "Can't open output file!" << std::endl;
        return EXIT_FAILURE;
    }

    outFile << "Coefficients of a polynomial of degree " << degree << ":\n";
    int i = 0;
    for (double coeff : coeffs) {
        outFile << " x^" << i++ << ": " << coeff << std::endl;
    }
    outFile << "Elapsed time (sec): " << elapsedTime << std::endl;
    outFile.close();
    return true;
}


bool performanceTest(const std::string& fileName, std::vector<double>& x, std::vector<double>& y, int& degree) {
    size_t pos = fileName.find(".txt");
    std::string inputDataTxtName = fileName;
    if (pos != std::string::npos) {
        inputDataTxtName = fileName.substr(0, pos);  
    }

    std::ofstream timeFile(inputDataTxtName + "_threads_execution_time.txt");
    if (!timeFile.is_open()) {
        std::cerr << "Can't open output file!" << std::endl;
        return EXIT_FAILURE;
    }

    for (int numThreads = 1; numThreads <= 8; ++numThreads) {
        omp_set_num_threads(numThreads);

        std::vector<std::vector<double>> A(degree + 1, std::vector<double>(degree + 1, 0.0));
        std::vector<double> b(degree + 1, 0.0);

        double t1 = fillMatrix(x, y, A, b, degree);
        std::vector<double> coeffs(degree + 1, 0.0);
        double t2 = gaussElim(A, b, coeffs);
        double elapsedTime = t1 + t2;

        timeFile << numThreads << " " << elapsedTime << std::endl;
    }
    std::cout << "Threads performance test is completed" << std::endl;
    return true;
}