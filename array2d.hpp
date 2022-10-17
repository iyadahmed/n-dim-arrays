#pragma once

#include <cassert>
#include <utility> // for std::swap
#include <memory>  // for std::shared_ptr

// Why not templates to set number of rows and columns and allocate array on stack without alloca?
// Answer: assume we want to create A LOT of matrices with different shapes?
// There is an overhead (at least in generated code size)

class Array2D
{
private:
    std::shared_ptr<float[]> data;
    int offset = 0;
    int num_rows = 0;
    int num_cols = 0;
    int row_stride = 0;
    int col_stride = 0;

    int calc_offset(int row_index, int col_index) const
    {
        return offset + row_index * row_stride + col_index * col_stride;
    }

public:
    Array2D(int num_rows, int num_cols)
        : offset(0),
          num_rows(num_rows),
          num_cols(num_cols),
          row_stride(num_cols),
          col_stride(1)
    {
        data = std::shared_ptr<float[]>(new float[num_rows * num_cols]);
    }

    Array2D(std::shared_ptr<float[]> data, int offset, int num_rows, int num_cols, int row_stride, int col_stride)
        : data(data),
          offset(offset),
          num_rows(num_rows),
          num_cols(num_cols),
          row_stride(row_stride),
          col_stride(col_stride)
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

    Array2D get_row(int row_index) const
    {
        return Array2D{data, (row_index * row_stride), 1, num_cols, row_stride, col_stride};
    }

    Array2D get_column(int col_index) const
    {
        return Array2D(data, col_index, num_rows, 1, row_stride, col_stride);
    }

    int get_num_cols() const
    {
        return num_cols;
    }

    int get_num_rows() const
    {
        return num_rows;
    }

    Array2D mat_mul(const Array2D &other) const
    {
        assert(num_cols == other.num_rows);

        Array2D out(num_rows, other.num_cols);

        for (int i = 0; i < out.num_rows; i++)
        {
            for (int j = 0; j < out.num_cols; j++)
            {
                Array2D row = get_row(i);
                Array2D col = other.get_column(j);

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

    void transpose()
    {
        std::swap(row_stride, col_stride);
        std::swap(num_rows, num_cols);
    }
};
