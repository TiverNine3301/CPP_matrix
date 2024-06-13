#include "s21_matrix_oop.h"

void S21Matrix::create_matrix(S21Matrix& other, int rows, int cols) {
  if (rows < 1 || cols < 1)
    throw std::out_of_range("Incorrect input, indices less than 1");
  other.rows_ = rows;
  other.cols_ = cols;
  other.matrix_ = new double*[other.rows_]();
  for (int i = 0; i < other.rows_; i++)
    other.matrix_[i] = new double[other.cols_]();
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) other.matrix_[i][j] = 0.0;
  }
}

void S21Matrix::sum_sub_matrix(const S21Matrix& other, int s) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::out_of_range(
        "Incorrect input, matrices should have the same size");
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] += s * other.matrix_[i][j];
    }
  }
}

void S21Matrix::s21_matrix_minor(S21Matrix& other, int p, int q) {
  int i = 0, j = 0;
  for (int row = 0; row < rows_; row++) {
    for (int col = 0; col < cols_; col++) {
      if (row != p && col != q) {
        other.matrix_[i][j++] = matrix_[row][col];
        if (j == cols_ - 1) {
          j = 0;
          i++;
        }
      }
    }
  }
}