#pragma once

#include <cassert>

// Why not templates to set number of rows and columns and allocate array on stack without alloca?
// Answer: assume we want to create A LOT of matrices with different shapes?
// There is an overhead (at least in generated code size)

class Matrix2D
{
private:
    float *data = nullptr;
    const int num_rows = 0, num_cols = 0;
    const int row_stride = 0; // TODO: add column stride for "fast transpose"

    int calc_offset(int row_index, int col_index) const
    {
        return row_index * row_stride + col_index;
    }

public:
    Matrix2D(int num_rows, int num_cols) : num_rows(num_rows), num_cols(num_cols), row_stride(num_cols)
    {
        // FIXME: free this and handle copy and move constructor (or delete those constructors)
        data = new float[num_rows * num_cols];
    }

    Matrix2D(float *data, int num_rows, int num_cols, int row_stride) : data(data), num_rows(num_rows), num_cols(num_cols), row_stride(row_stride)
    {
    }

    float &element(int row_index, int col_index)
    {
        return data[calc_offset(row_index, col_index)];
    }

    const float &element(int row_index, int col_index) const
    {
        return data[calc_offset(row_index, col_index)];
    }

    Matrix2D get_row(int row_index) const
    {
        return Matrix2D(data + (row_index * row_stride), 1, num_cols, num_cols);
    }

    Matrix2D get_column(int col_index) const
    {
        return Matrix2D(data + col_index, num_rows, 1, num_cols);
    }

    int get_num_cols() const
    {
        return num_cols;
    }

    int get_num_rows() const
    {
        return num_rows;
    }

    Matrix2D mat_mul(const Matrix2D &other) const
    {
        assert(num_cols == other.num_rows);

        Matrix2D out(num_rows, other.num_cols);

        for (int i = 0; i < out.num_rows; i++)
        {
            for (int j = 0; j < out.num_cols; j++)
            {
                Matrix2D row = get_row(i);
                Matrix2D col = other.get_column(j);

                float &out_elem = out.element(i, j);
                out_elem = 0.0f;

                // Dot product of row and column
                for (int i = 0; i < row.get_num_cols(); i++)
                {
                    out_elem += row.element(0, i) * col.element(i, 0);
                }
            }
        }

        return out;
    }
};
