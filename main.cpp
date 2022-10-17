#include <iostream>
#include <cstdio>
#include "ndarray.hpp"

int main()
{
    freopen("./test_input.txt", "r", stdin);

    Matrix2D A(4, 4), B(4, 4);

    std::cout << "Enter first 4x4 matrix elements" << std::endl;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            std::cin >> A.element(i, j);
        }
    }
    std::cout << "\n";

    std::cout << "Enter second 4x4 matrix elements" << std::endl;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            std::cin >> B.element(i, j);
        }
    }
    std::cout << "\n";

    auto result = A.mat_mul(B);
    std::cout << "Matrix Multiplication Result = \n";

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            std::cout << result.element(i, j) << "\t";
        }
        std::cout << "\n";
    }
}