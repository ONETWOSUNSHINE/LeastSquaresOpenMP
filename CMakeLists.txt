cmake_minimum_required(VERSION 3.10)
project(LeastSquaresOpenMP)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenMP REQUIRED)

add_executable(lsq lsq.cpp gauss_elim.cpp poly_fit.cpp utils.cpp)

target_link_libraries(lsq PRIVATE OpenMP::OpenMP_CXX)
