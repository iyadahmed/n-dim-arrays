#pragma once

#include <iostream>
#include "ndarray.hpp"

Matrix2D read_matrix_from_stdin()
{
    int num_rows, num_cols;

    std::cout << "Enter matrix dimensions: " << std::endl;
    std::cin >> num_rows >> num_cols;

    Matrix2D matrix(num_rows, num_cols);

    std::cout << "Enter matrix elements: " << std::endl;
    for (int i = 0; i < num_rows; i++)
    {
        for (int j = 0; j < num_cols; j++)
        {
            std::cin >> matrix.element(i, j);
        }
    }
    std::cout << "\n";

    return matrix;
}

void print_matrix(const Matrix2D &matrix)
{
    for (int i = 0; i < matrix.get_num_rows(); i++)
    {
        for (int j = 0; j < matrix.get_num_cols(); j++)
        {
            std::cout << matrix.element(i, j) << "\t";
        }
        std::cout << "\n";
    }
}