#ifndef __MATRIX_H__
#define __MATRIX_H__

#include <valarray>
#include <vector>
#include <numeric>
#include <iostream>
class Matrix
{
private:
    std::valarray<double> m_matrix;
    unsigned int m_rows;
    unsigned int m_cols;
public:
    Matrix(unsigned int rows, unsigned int cols, const std::valarray<double> &matrix) :
        m_matrix(matrix),
        m_rows(rows),
        m_cols(cols) {}
    Matrix(unsigned int rows, unsigned int cols, double initial = 0.0) :
        m_matrix(initial, rows * cols),
        m_rows(rows),
        m_cols(cols) {}
    ~Matrix() = default;

    //Matrix
    // Matrix Math
    Matrix operator+(const Matrix &rhs);
    Matrix& operator+=(const Matrix & rhs);
    Matrix operator-(const Matrix &rhs);
    Matrix& operator-=(const Matrix &rhs);
    Matrix operator*(const Matrix &rhs);
    Matrix& operator*=(const Matrix &rhs);
    Matrix transpose();

    // Scalar Math
    Matrix operator+(const double &rhs);
    Matrix& operator+=(const double & rhs);
    Matrix operator-(const double &rhs);
    Matrix& operator-=(const double &rhs);
    Matrix operator*(const double &rhs);
    Matrix& operator*=(const double &rhs);
    Matrix operator/(const double &rhs);
    Matrix& operator/=(const double &rhs);

    //accessors
    double& operator()(unsigned row, unsigned col);
    const double& operator()(unsigned row, unsigned col) const;

    void PrintMatrix();

    unsigned int GetRows() const;
    unsigned int GetCols() const;
};

double& Matrix::operator()(unsigned row, unsigned col) 
{
    return this->m_matrix[row * this->m_cols + col];
}

const double& Matrix::operator()(unsigned row, unsigned col) const
{
    return this->m_matrix[row * this->m_cols + col];
}

Matrix Matrix::operator+(const Matrix &rhs) 
{
    return Matrix(this->m_rows, this->m_cols, this->m_matrix + rhs.m_matrix);
}

Matrix& Matrix::operator+=(const Matrix & rhs) 
{
    (*this) = (*this) + rhs;
    return *this;
}

Matrix Matrix::operator-(const Matrix &rhs) 
{
    return Matrix(this->m_rows, this->m_cols, this->m_matrix - rhs.m_matrix);
}

Matrix& Matrix::operator-=(const Matrix &rhs) 
{
    (*this) = (*this) - rhs;
    return *this;
}

Matrix Matrix::operator*(const Matrix &rhs) 
{
    auto rows = this->m_rows;
    auto cols = rhs.m_cols;
    Matrix result(rows, cols);
    for (size_t i = 0; i < rows; i++)
    {
        const std::valarray<double> &lhs_row = this->m_matrix[std::slice(i * this->m_cols, this->m_cols, 1)];
        for (size_t j = 0; j < cols; j++)
        {
            const std::valarray<double> &rhs_col = rhs.m_matrix[std::slice(j,rhs.m_rows,cols)];
            auto x = std::inner_product(std::begin(lhs_row), std::end(lhs_row), std::begin(rhs_col),0);
            result(i,j) = std::inner_product(std::begin(lhs_row), std::end(lhs_row), std::begin(rhs_col),0);
        }
    }
    return result;
}

Matrix& Matrix::operator*=(const Matrix &rhs) 
{
    (*this) = (*this) * rhs;
    return *this;
}

Matrix Matrix::transpose() 
{
    Matrix result(m_cols, m_rows);
    for (size_t i = 0; i < m_rows; i++)
    {
        for (size_t j = 0; j < m_cols; j++)
        {
            result(i,j) = (*this)(j,i);
        }
    }
    return result;
}

Matrix Matrix::operator+(const double &rhs) 
{
    return Matrix(m_rows, m_cols, m_matrix + rhs);
}

Matrix& Matrix::operator+=(const double &rhs) 
{
    (*this) = (*this) + rhs;
    return *this;
}

Matrix Matrix::operator-(const double &rhs) 
{
    return Matrix(m_rows, m_cols, m_matrix - rhs);
}

Matrix& Matrix::operator-=(const double &rhs) 
{
    (*this) = (*this) - rhs;
    return *this;
}

Matrix Matrix::operator*(const double &rhs) 
{
    return Matrix(m_rows, m_cols, m_matrix * rhs);
}

Matrix& Matrix::operator*=(const double &rhs) 
{
    (*this) = (*this) * rhs;
    return *this;
}

Matrix Matrix::operator/(const double &rhs) 
{
    return Matrix(m_rows, m_cols, m_matrix / rhs);
}

Matrix& Matrix::operator/=(const double &rhs) 
{
    (*this) = (*this) / rhs;
    return *this;
}

void Matrix::PrintMatrix() 
{
    for (size_t i = 0; i < m_rows * m_cols; i++)
    {
        std::cout << m_matrix[i] << " ";
        if((i + 1) % m_cols == 0)
        {
            std::cout << "\n";
        }
    }
}

unsigned int Matrix::GetRows() const
{
    return m_rows;
}

unsigned int Matrix::GetCols() const
{
    return m_cols;
}



#endif // __MATRIX_H__