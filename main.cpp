#include <iostream>
#include <cstdio>

#include "array2d.hpp"
#include "utils.hpp"

int main()
{
    freopen("./test_input.txt", "r", stdin);

    Array2D A = read_matrix_from_stdin();
    Array2D B = read_matrix_from_stdin();
    Array2D result = A.mat_mul(B);

    std::cout << "Matrix Multiplication Result = \n";
    print_matrix(result);
}