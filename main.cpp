#include <iostream>
#include <cstdio>

#include "ndarray.hpp"
#include "utils.hpp"

int main()
{
    freopen("./test_input.txt", "r", stdin);

    Matrix2D A = read_matrix_from_stdin();
    Matrix2D B = read_matrix_from_stdin();
    Matrix2D result = A.mat_mul(B);

    std::cout << "Matrix Multiplication Result = \n";
    print_matrix(result);
}