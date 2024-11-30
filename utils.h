#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <string>

bool readData(const std::string& filename, std::vector<double>& x, std::vector<double>& y, int& degree);
bool performanceTest(const std::string& fileName, std::vector<double>& x, std::vector<double>& y, int& degree);
bool writeResultsToFile(const std::vector<double>& coeffs, int degree, double elapsedTime, const std::string& filename);

#endif /* UTILS_H */
