#include "../src/binary_arithmetic.hpp"

void multiplication_mat_vect(Matrix mat, Vector vect) {
  mat * vect;
}

void equal_mat(Matrix mat1, Matrix mat2) {
  mat1 == mat1;
}

void comparaisons_mat(Matrix mat1, Matrix mat2) {
  mat1 < mat1;
}

void additions_mat(Matrix mat1, Matrix mat2) {
  mat1 + mat2;
}

void multiplication_mat(Matrix mat1, Matrix mat2) {
  mat1 * mat2;
}

void scalar_product_mat(Matrix mat1, Matrix mat2) {
  mat1 % mat2;
}

void integer_scalar_product_mat(Matrix mat1, Matrix mat2) {
  mat1 / mat2;
}

void negation_mat(Matrix mat) {
  ~mat;
}

void transposition(Matrix mat) {
  mat.T();
}

void equal_vect(Vector vect1, Vector vect2) {
  vect1 == vect2;
}

void comparaisons_vect(Vector vect1, Vector vect2) {
  vect1 < vect2;
}

void additions_vect(Vector vect1, Vector vect2) {
  vect1 + vect2;
}

void multiplication_vect(Vector vect1, Vector vect2) {
  vect1 * vect2;
}

void scalar_product_vect(Vector vect1, Vector vect2) {
  vect1 % vect2;
}

void integer_scalar_product_vect(Vector vect1, Vector vect2) {
  vect1 / vect2;
}

void negation_vect(Vector vect) {
  ~vect;
}
