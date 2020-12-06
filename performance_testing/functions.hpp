#include "../binary_arithmetic/binary_arithmetic.hpp"

void multiplication_mat_vect(Matrice mat, Vector vect) {
  mat * vect;
}

void equal_mat(Matrice mat1, Matrice mat2) {
  mat1 == mat1;
}

void comparaisons_mat(Matrice mat1, Matrice mat2) {
  mat1 < mat1;
}

void additions_mat(Matrice mat1, Matrice mat2) {
  mat1 + mat2;
}

void multiplication_mat(Matrice mat1, Matrice mat2) {
  mat1 * mat2;
}

void scalar_product_mat(Matrice mat1, Matrice mat2) {
  mat1 % mat2;
}

void integer_scalar_product_mat(Matrice mat1, Matrice mat2) {
  mat1.integer_scalar_product(mat2);
}

void negation_mat(Matrice mat) {
  ~mat;
}

void transposition(Matrice mat) {
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
  vect1.integer_scalar_product(vect2);
}

void negation_vect(Vector vect) {
  ~vect;
}
