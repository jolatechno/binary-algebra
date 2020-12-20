#pragma once

#include "../src/reference_arithmetic/reference_arithmetic.hpp"
#include "../src/binary_arithmetic.hpp"

#include <cassert>

/*
multiplications
*/


void test_self_multiplication(const reference_arithmetic ref, Matrix& mat1, Matrix const& mat2) {
  Matrix stupid_product = ref.multiplication(mat1, mat2);
  mat1 *= mat2;

  assert(ref.equal(mat1, stupid_product));
}

void test_self_multiplication(const reference_arithmetic ref, Matrix& mat, Vector& vect) {
  Vector stupid_product = ref.multiplication(mat, vect);
  vect *= mat;

  assert(ref.equal(vect, stupid_product));
}


/*
additions
*/


void test_self_addition(const reference_arithmetic ref, Matrix& mat1, Matrix const& mat2) {
  Matrix stupid_add = ref.addition(mat1, mat2);
  mat1 ^= mat2;

  assert(ref.equal(mat1, stupid_add));
}

void test_self_addition(const reference_arithmetic ref, Matrix& mat, bool bit) {
  Matrix stupid_add = ref.addition(mat, bit);
  mat ^= bit;

  assert(ref.equal(mat, stupid_add));
}

void test_self_addition(const reference_arithmetic ref, Vector& vect1, Vector const& vect2) {
  Vector stupid_add = ref.addition(vect1, vect2);
  vect1 ^= vect2;

  assert(ref.equal(vect1, stupid_add));
}

void test_self_addition(const reference_arithmetic ref, Vector& vect, bool bit) {
  Vector stupid_add = ref.addition(vect, bit);
  vect ^= bit;

  assert(ref.equal(vect, stupid_add));
}


/*
bitwise multiplication
*/


void test_self_bitwise_multiplication(const reference_arithmetic ref, Matrix& mat1, Matrix const& mat2) {
  Matrix stupid_mul = ref.bitwise_multiplication(mat1, mat2);
  mat1 &= mat2;

  assert(ref.equal(mat1, stupid_mul));
}

void test_self_bitwise_multiplication(const reference_arithmetic ref, Matrix& mat, bool bit) {
  Matrix stupid_mul = ref.bitwise_multiplication(mat, bit);
  mat &= bit;

  assert(ref.equal(mat, stupid_mul));
}

void test_self_bitwise_multiplication(const reference_arithmetic ref, Vector& vect1, Vector const& vect2) {
  Vector stupid_mul = ref.bitwise_multiplication(vect1, vect2);
  vect1 &= vect2;

  assert(ref.equal(vect1, stupid_mul));
}
void test_self_bitwise_multiplication(const reference_arithmetic ref, Vector& vect, bool bit) {
  Vector stupid_mul = ref.bitwise_multiplication(vect, bit);
  vect &= bit;

  assert(ref.equal(vect, stupid_mul));
}
