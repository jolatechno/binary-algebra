#pragma once

#include "../src/reference_arithmetic/reference_arithmetic.hpp"
#include "../src/binary_arithmetic.hpp"

#include <cassert>
#include <stdint.h>
#include <stdbool.h>

/*
testing comparaisons
*/


void test_comp(const reference_arithmetic ref, Matrix const& mat1, Matrix const& mat2) {
  assert((mat1 == mat2) == ref.equal(mat1, mat2));
  assert((mat1 != mat2) != ref.equal(mat1, mat2));

  assert((mat1 > mat2) == ref.greater(mat1, mat2));
  assert((mat1 <= mat2) != ref.greater(mat1, mat2));

  assert((mat1 < mat2) == ref.greater(mat2, mat1));
  assert((mat1 >= mat2) != ref.greater(mat2, mat1));
}

void test_comp(const reference_arithmetic ref, Vector const& vect1, Vector const& vect2) {
  assert((vect1 == vect2) == ref.equal(vect1, vect2));
  assert((vect1 != vect2) != ref.equal(vect1, vect2));

  assert((vect1 > vect2) == ref.greater(vect1, vect2));
  assert((vect1 <= vect2) != ref.greater(vect1, vect2));

  assert((vect1 < vect2) == ref.greater(vect2, vect1));
  assert((vect1 >= vect2) != ref.greater(vect2, vect1));
}

void test_comp(const reference_arithmetic ref, Matrix const& mat, bool bit) {
  assert((mat == bit) == ref.equal(mat, bit));
  assert((mat != bit) != ref.equal(mat, bit));
}

void test_comp(const reference_arithmetic ref, Vector const& vect, bool bit) {
  assert((vect == bit) == ref.equal(vect, bit));
  assert((vect != bit) != ref.equal(vect, bit));
}
