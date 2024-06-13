#include "s21_matrix_oop.h"

S21Matrix::S21Matrix() {
  rows_ = 0;
  cols_ = 0;
  matrix_ = nullptr;
}

S21Matrix::S21Matrix(const S21Matrix& other) {
  create_matrix(*this, other.rows_, other.cols_);
  for (int i = 0; i < other.rows_; i++) {
    for (int j = 0; j < other.cols_; j++) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

S21Matrix::S21Matrix(S21Matrix&& other) {
  rows_ = other.rows_;
  cols_ = other.cols_;
  matrix_ = other.matrix_;
  other.matrix_ = nullptr;
  other.rows_ = 0;
  other.cols_ = 0;
}

S21Matrix::~S21Matrix() {
  for (int i = 0; i < rows_; i++) delete[] matrix_[i];
  delete[] matrix_;
  rows_ = 0;
  cols_ = 0;
}

S21Matrix::S21Matrix(int rows, int cols) { create_matrix(*this, rows, cols); }

bool S21Matrix::EqMatrix(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    return false;
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      if (matrix_[i][j] != other.matrix_[i][j]) {
        return false;
      }
    }
  }
  return true;
}

int S21Matrix::getRows() const { return rows_; }

int S21Matrix::getCols() const { return cols_; }

void S21Matrix::setRows(int rows) {
  if (rows_ == rows) return;
  if (rows < rows_) {
    double** newMatrix = new double*[rows];
    for (int i = 0; i < rows; i++) {
      newMatrix[i] = matrix_[i];
    }
    for (int i = rows; i < rows_; i++) delete[] matrix_[i];
    delete[] matrix_;
    matrix_ = newMatrix;
    rows_ = rows;
    return;
  }
  int oldRows = rows_;
  rows_ = rows;
  double** newMatrix = new double*[rows_];
  for (int i = 0; i < oldRows; i++) {
    newMatrix[i] = matrix_[i];
  }
  for (int i = oldRows; i < rows_; i++) {
    newMatrix[i] = new double[cols_];
    for (int j = 0; j < cols_; j++) {
      newMatrix[i][j] = 0.0;
    }
  }
  delete[] matrix_;
  matrix_ = newMatrix;
}

void S21Matrix::setCols(int cols) {
  if (cols_ == cols) return;
  if (cols < cols_) {
    for (int i = 0; i < rows_; i++) {
      double* new_row = new double[cols];
      for (int j = 0; j < cols; j++) {
        new_row[j] = matrix_[i][j];
      }
      delete[] matrix_[i];
      matrix_[i] = new_row;
    }
    cols_ = cols;
    return;
  }
  for (int i = 0; i < rows_; ++i) {
    double* new_row = new double[cols];
    for (int j = 0; j < cols_; ++j) {
      new_row[j] = matrix_[i][j];
    }
    for (int j = cols_; j < cols; ++j) {
      new_row[j] = 0.0;
    }
    delete[] matrix_[i];
    matrix_[i] = new_row;
  }
  cols_ = cols;
}

void S21Matrix::SumMatrix(const S21Matrix& other) { sum_sub_matrix(other, 1); }

void S21Matrix::SubMatrix(const S21Matrix& other) { sum_sub_matrix(other, -1); }

void S21Matrix::MulNumber(const double num) {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] *= num;
    }
  }
}

void S21Matrix::MulMatrix(const S21Matrix& other) {
  if (cols_ != other.rows_)
    throw std::out_of_range(
        "Incorrect input, matrices should have the same size");
  S21Matrix result(rows_, other.cols_);
  for (int i = 0; i < result.rows_; i++) {
    for (int j = 0; j < result.cols_; j++) {
      for (int k = 0; k < cols_; k++)
        result.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
    }
  }
  *this = std::move(result);
}

S21Matrix S21Matrix::Transpose() {
  S21Matrix result(cols_, rows_);
  for (int i = 0; i < cols_; i++)
    for (int j = 0; j < rows_; j++) {
      result.matrix_[i][j] = matrix_[j][i];
    }
  return result;
}

double S21Matrix::Determinant() {
  if (cols_ != rows_)
    throw std::out_of_range(
        "Incorrect input, matrices should have the same size");
  if (rows_ == 1 && cols_ == 1) return matrix_[0][0];
  S21Matrix result{rows_ - 1, cols_ - 1};
  double sign = 1.0;
  double det = 0.0;
  for (int f = 0; f < cols_; f++) {
    s21_matrix_minor(result, 0, f);
    double sub_det = 0.0;
    sub_det = result.Determinant();
    det += sign * matrix_[0][f] * sub_det;
    sign = -sign;
  }
  return det;
}

S21Matrix S21Matrix::CalcComplements() {
  if (cols_ != rows_)
    throw std::out_of_range(
        "Incorrect input, matrices should have the same size");
  S21Matrix result(rows_, cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      S21Matrix sub_matrix{rows_ - 1, cols_ - 1};
      s21_matrix_minor(sub_matrix, i, j);
      double det = sub_matrix.Determinant();
      double sign = pow(-1, i + j);
      result.matrix_[i][j] = det * sign;
    }
  }
  return result;
}

S21Matrix S21Matrix::InverseMatrix() {
  double det = this->Determinant();
  if (det == 0) {
    throw std::out_of_range("There is no inverse because the determinant is 0");
  }
  S21Matrix result = this->CalcComplements().Transpose();
  result.MulNumber(1 / det);
  return result;
}

S21Matrix S21Matrix::operator+=(const S21Matrix& other) {
  SumMatrix(other);
  return *this;
}

S21Matrix S21Matrix::operator-=(const S21Matrix& other) {
  SubMatrix(other);
  return *this;
}

S21Matrix S21Matrix::operator*=(const S21Matrix& other) {
  MulMatrix(other);
  return *this;
}

S21Matrix& S21Matrix::operator*=(const double other) {
  MulNumber(other);
  return *this;
}

bool S21Matrix::operator==(const S21Matrix& other) { return EqMatrix(other); }

S21Matrix S21Matrix::operator+(const S21Matrix& other) {
  S21Matrix result = *this;
  result.SumMatrix(other);
  return result;
}

S21Matrix S21Matrix::operator-(const S21Matrix& other) {
  S21Matrix result = *this;
  result.SubMatrix(other);
  return result;
}

S21Matrix S21Matrix::operator*(const double other) {
  S21Matrix result = *this;
  result.MulNumber(other);
  return result;
}

S21Matrix S21Matrix::operator*(const S21Matrix& other) {
  S21Matrix result = *this;
  result.MulMatrix(other);
  return result;
}

double& S21Matrix::operator()(int x, int y) {
  if (x >= rows_ || x < 0 || y >= cols_ || y < 0)
    throw std::out_of_range("Index per matrix difference");
  return matrix_[x][y];
}

S21Matrix& S21Matrix::operator=(const S21Matrix& other) {
  if (EqMatrix(other)) return *this;
  if (matrix_) {
    for (int i = 0; i < rows_; i++) delete[] matrix_[i];
    delete[] matrix_;
  }
  create_matrix(*this, other.rows_, other.cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
  return *this;
}

S21Matrix& S21Matrix::operator=(S21Matrix&& other) {
  std::swap(rows_, other.rows_);
  std::swap(cols_, other.cols_);
  std::swap(matrix_, other.matrix_);
  return *this;
}
