#include "s21_matrix_oop.h"

#include "gtest/gtest.h"

TEST(S21Matrix0, Constructor) {
  S21Matrix matrix(3, 3);
  EXPECT_EQ(matrix.getRows(), 3);
  EXPECT_EQ(matrix.getCols(), 3);
}

TEST(S21Matrix1, Constructor) {
  S21Matrix matrix(3, 3);
  matrix(0, 0) = 5;
  EXPECT_EQ(matrix(0, 0), 5);
}

TEST(S21Matrix2, Constructor) {
  S21Matrix matrix(3, 3);
  EXPECT_EQ(matrix(0, 0), 0);
}

TEST(S21Matrix3, Constructor) {
  S21Matrix a;
  EXPECT_EQ(a.getRows(), 0);
  EXPECT_EQ(a.getCols(), 0);
}

TEST(S21Matrix4, Constructor) {
  S21Matrix b(3, 3);
  for (int i = 0; i < b.getRows(); i++) {
    for (int j = 0; j < b.getCols(); j++) {
      b(i, j) = i + j;
      EXPECT_EQ(b(i, j), i + j);
    }
  }
  S21Matrix c(b);
  for (int i = 0; i < c.getRows(); i++) {
    for (int j = 0; j < c.getCols(); j++) {
      EXPECT_EQ(b(i, j), i + j);
      EXPECT_EQ(c(i, j), i + j);
    }
  }
  S21Matrix d(std::move(b));
  EXPECT_EQ(b.getRows(), 0);
  EXPECT_EQ(b.getCols(), 0);
  for (int i = 0; i < d.getRows(); i++) {
    for (int j = 0; j < d.getCols(); j++) {
      EXPECT_EQ(d(i, j), i + j);
    }
  }
}

TEST(S21Matrix5, Operation) {
  S21Matrix A(2, 2);
  S21Matrix B(2, 2);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(1, 0) = 3;
  A(1, 1) = 4;
  B(0, 0) = 1;
  B(0, 1) = 2;
  B(1, 0) = 3;
  B(1, 1) = 4;
  A.SumMatrix(B);
  EXPECT_EQ(A(0, 0), 2);
  EXPECT_EQ(A(0, 1), 4);
  EXPECT_EQ(A(1, 0), 6);
  EXPECT_EQ(A(1, 1), 8);
}

TEST(S21Matrix6, Operation) {
  S21Matrix A(2, 2);
  S21Matrix B(2, 2);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(1, 0) = 3;
  A(1, 1) = 4;
  B(0, 0) = 1;
  B(0, 1) = 2;
  B(1, 0) = 3;
  B(1, 1) = 4;
  A.SubMatrix(B);
  EXPECT_EQ(A(0, 0), 0);
  EXPECT_EQ(A(0, 1), 0);
  EXPECT_EQ(A(1, 0), 0);
  EXPECT_EQ(A(1, 1), 0);
}

TEST(S21Matrix7, Operation) {
  S21Matrix A(2, 2);
  double a = 2;
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(1, 0) = 3;
  A(1, 1) = 4;
  A.MulNumber(a);
  EXPECT_EQ(A(0, 0), 2);
  EXPECT_EQ(A(0, 1), 4);
  EXPECT_EQ(A(1, 0), 6);
  EXPECT_EQ(A(1, 1), 8);
}

TEST(S21Matrix8, Operation) {
  S21Matrix A(2, 2);
  S21Matrix B(2, 2);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(1, 0) = 3;
  A(1, 1) = 4;
  B(0, 0) = 1;
  B(0, 1) = 2;
  B(1, 0) = 3;
  B(1, 1) = 4;
  A.MulMatrix(B);
  EXPECT_EQ(A(0, 0), 7);
  EXPECT_EQ(A(0, 1), 10);
  EXPECT_EQ(A(1, 0), 15);
  EXPECT_EQ(A(1, 1), 22);
}

TEST(S21Matrix9, Operation) {
  S21Matrix A(2, 2);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(1, 0) = 3;
  A(1, 1) = 4;
  S21Matrix B = A.Transpose();
  EXPECT_EQ(B(0, 0), 1);
  EXPECT_EQ(B(0, 1), 3);
  EXPECT_EQ(B(1, 0), 2);
  EXPECT_EQ(B(1, 1), 4);
}

TEST(S21Matrix10, Operation) {
  S21Matrix A(2, 2);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(1, 0) = 3;
  A(1, 1) = 4;
  S21Matrix B = A.InverseMatrix();
  EXPECT_EQ(B(0, 0), -2);
  EXPECT_EQ(B(0, 1), 1);
  EXPECT_EQ(B(1, 0), 1.5);
  EXPECT_EQ(B(1, 1), -0.5);
}

TEST(S21Matrix11, Operator) {
  S21Matrix A(2, 2);
  S21Matrix B(2, 2);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(1, 0) = 3;
  A(1, 1) = 4;
  B(0, 0) = 1;
  B(0, 1) = 2;
  B(1, 0) = 3;
  B(1, 1) = 4;
  S21Matrix C = A - B;
  EXPECT_EQ(C(0, 0), 0);
  EXPECT_EQ(C(0, 1), 0);
  EXPECT_EQ(C(1, 0), 0);
  EXPECT_EQ(C(1, 1), 0);
}

TEST(S21Matrix12, Operator) {
  S21Matrix A(2, 2);
  S21Matrix B(2, 2);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(1, 0) = 3;
  A(1, 1) = 4;
  B(0, 0) = 1;
  B(0, 1) = 2;
  B(1, 0) = 3;
  B(1, 1) = 4;
  S21Matrix C = A + B;
  EXPECT_EQ(C(0, 0), 2);
  EXPECT_EQ(C(0, 1), 4);
  EXPECT_EQ(C(1, 0), 6);
  EXPECT_EQ(C(1, 1), 8);
}

TEST(S21Matrix13, Operator) {
  S21Matrix A(2, 2);
  double a = 2;
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(1, 0) = 3;
  A(1, 1) = 4;
  S21Matrix B = A * a;
  EXPECT_EQ(B(0, 0), 2);
  EXPECT_EQ(B(0, 1), 4);
  EXPECT_EQ(B(1, 0), 6);
  EXPECT_EQ(B(1, 1), 8);
}

TEST(S21Matrix14, Operation) {
  S21Matrix A(2, 2);
  S21Matrix B(2, 2);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(1, 0) = 3;
  A(1, 1) = 4;
  B(0, 0) = 1;
  B(0, 1) = 2;
  B(1, 0) = 3;
  B(1, 1) = 4;
  EXPECT_EQ(A.EqMatrix(B), true);
}

TEST(S21Matrix15, Operator) {
  S21Matrix A(2, 2);
  S21Matrix B(2, 2);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(1, 0) = 3;
  A(1, 1) = 4;
  B(0, 0) = 1;
  B(0, 1) = 2;
  B(1, 0) = 3;
  B(1, 1) = 4;
  EXPECT_EQ(A == B, true);
}

TEST(S21Matrix16, Operator) {
  S21Matrix A(2, 2);
  S21Matrix B(2, 2);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(1, 0) = 3;
  A(1, 1) = 4;
  B(0, 0) = 1;
  B(0, 1) = 2;
  B(1, 0) = 3;
  B(1, 1) = 4;
  S21Matrix C = A * B;
  EXPECT_EQ(C(0, 0), 7);
  EXPECT_EQ(C(0, 1), 10);
  EXPECT_EQ(C(1, 0), 15);
  EXPECT_EQ(C(1, 1), 22);
}

TEST(S21Matrix17, Operator) {
  S21Matrix A(2, 2);
  S21Matrix B(2, 2);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(1, 0) = 3;
  A(1, 1) = 4;
  B(0, 0) = 4;
  B(0, 1) = 3;
  B(1, 0) = 2;
  B(1, 1) = 1;
  A += B;
  EXPECT_EQ(A(0, 0), 5);
  EXPECT_EQ(A(0, 1), 5);
  EXPECT_EQ(A(1, 0), 5);
  EXPECT_EQ(A(1, 1), 5);
}

TEST(S21Matrix18, Operator) {
  S21Matrix A(2, 2);
  S21Matrix B(2, 2);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(1, 0) = 3;
  A(1, 1) = 4;
  B(0, 0) = 4;
  B(0, 1) = 3;
  B(1, 0) = 2;
  B(1, 1) = 1;
  A -= B;
  EXPECT_EQ(A(0, 0), -3);
  EXPECT_EQ(A(0, 1), -1);
  EXPECT_EQ(A(1, 0), 1);
  EXPECT_EQ(A(1, 1), 3);
}

TEST(S21Matrix19, Operator) {
  S21Matrix A(2, 2);
  S21Matrix B(2, 2);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(1, 0) = 3;
  A(1, 1) = 4;
  B(0, 0) = 4;
  B(0, 1) = 3;
  B(1, 0) = 2;
  B(1, 1) = 1;
  A *= B;
  EXPECT_EQ(A(0, 0), 8);
  EXPECT_EQ(A(0, 1), 5);
  EXPECT_EQ(A(1, 0), 20);
  EXPECT_EQ(A(1, 1), 13);
}

TEST(S21Matrix20, Operator) {
  S21Matrix A(2, 2);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(1, 0) = 3;
  A(1, 1) = 4;
  A *= 2;
  EXPECT_EQ(A(0, 0), 2);
  EXPECT_EQ(A(0, 1), 4);
  EXPECT_EQ(A(1, 0), 6);
  EXPECT_EQ(A(1, 1), 8);
}

TEST(S21Matrix21, Operator) {
  S21Matrix A(2, 2);
  S21Matrix B(2, 2);
  A(0, 0) = 0;
  A(0, 1) = 0;
  A(1, 0) = 0;
  A(1, 1) = 0;
  B(0, 0) = 4;
  B(0, 1) = 3;
  B(1, 0) = 2;
  B(1, 1) = 1;
  A = B;
  EXPECT_EQ(A(0, 0), B(0, 0));
  EXPECT_EQ(A(0, 1), B(0, 1));
  EXPECT_EQ(A(1, 0), B(1, 0));
  EXPECT_EQ(A(1, 1), B(1, 1));
}

TEST(S21MATRIX22, Error) {
  S21Matrix A(2, 2);
  S21Matrix B(1, 1);
  A(0, 0) = 0;
  A(0, 1) = 0;
  A(1, 0) = 0;
  A(1, 1) = 0;
  B(0, 0) = 4;
  EXPECT_EQ(A.EqMatrix(B), false);
}

TEST(S21MATRIX23, Error) {
  S21Matrix A(2, 2);
  S21Matrix B(1, 1);
  A(0, 0) = 0;
  A(0, 1) = 0;
  A(1, 0) = 0;
  A(1, 1) = 0;
  B(0, 0) = 4;
  EXPECT_THROW(A.MulMatrix(B), std::out_of_range);
}

TEST(S21MATRIX24, Error) {
  S21Matrix A(2, 3);
  A(0, 0) = 1;
  A(0, 1) = 3;
  A(0, 2) = 5;
  A(1, 0) = 1;
  A(1, 1) = 4;
  A(1, 2) = 2;
  EXPECT_THROW(A.Determinant(), std::out_of_range);
}

TEST(S21MATRIX25, Error) {
  S21Matrix A(2, 3);
  A(0, 0) = 1;
  A(0, 1) = 3;
  A(0, 2) = 5;
  A(1, 0) = 1;
  A(1, 1) = 4;
  A(1, 2) = 2;
  EXPECT_THROW(A.CalcComplements(), std::out_of_range);
}

TEST(S21MATRIX26, Error) {
  S21Matrix A(2, 2);
  A(0, 0) = 0;
  A(0, 1) = 0;
  A(1, 0) = 0;
  A(1, 1) = 0;
  EXPECT_THROW(A.InverseMatrix(), std::out_of_range);
}

TEST(S21Matrix27, Error) {
  EXPECT_THROW(S21Matrix matrix(0, 0), std::out_of_range);
}

TEST(S21MATRIX28, Error) {
  S21Matrix A(2, 2);
  S21Matrix B(1, 1);
  A(0, 0) = 0;
  A(0, 1) = 0;
  A(1, 0) = 0;
  A(1, 1) = 0;
  B(0, 0) = 4;
  EXPECT_THROW(A.SumMatrix(B), std::out_of_range);
}

TEST(S21MATRIX29, Error) {
  S21Matrix A(2, 2);
  S21Matrix B(1, 1);
  A(0, 0) = 0;
  A(0, 1) = 0;
  A(1, 0) = 0;
  A(1, 1) = 0;
  B(0, 0) = 4;
  EXPECT_THROW(A.SubMatrix(B), std::out_of_range);
}

TEST(S21Matrix30, Constructor) {
  S21Matrix matrix(3, 3);
  matrix.setRows(2);
  matrix.setCols(2);
  EXPECT_EQ(matrix.getRows(), 2);
  EXPECT_EQ(matrix.getCols(), 2);
}

TEST(S21Matrix31, Constructor) {
  S21Matrix matrix(3, 3);
  matrix.setRows(4);
  matrix.setCols(4);
  EXPECT_EQ(matrix.getRows(), 4);
  EXPECT_EQ(matrix.getCols(), 4);
}

TEST(S21MATRIX32, Error) {
  S21Matrix A(2, 2);
  EXPECT_THROW(A(3, 3), std::out_of_range);
}
int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}