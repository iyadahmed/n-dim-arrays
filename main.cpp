#include <iostream>
#include <cstdio>

#include "ndarray.hpp"
#include "utils.hpp"

int main()
{
    freopen("./test_input.txt", "r", stdin);

    NDArray A = read_matrix_from_stdin();
    NDArray B = read_matrix_from_stdin();
    NDArray result = A.mat_mul(B);

    std::cout << "Matrix Multiplication Result = \n";
    print_matrix(result);
}