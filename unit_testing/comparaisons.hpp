#pragma once

#include "../binary_arithmetic/reference_arithmetic/reference_arithmetic.hpp"
#include "../binary_arithmetic/binary_arithmetic.hpp"

#include <cassert>
#include <stdint.h>
#include <stdbool.h>

/*
testing comparaisons
*/


void test_equal(const reference_arithmetic ref, Matrice const& mat1, Matrice const& mat2) {
  assert((mat1 == mat2) == ref.equal(mat1, mat2));
}

void test_equal(const reference_arithmetic ref, Vector const& vect1, Vector const& vect2) {
  assert((vect1 == vect2) == ref.equal(vect1, vect2));
}

void test_nequal(const reference_arithmetic ref, Matrice const& mat1, Matrice const& mat2) {
  assert((mat1 != mat2) == ref.nequal(mat1, mat2));
}

void test_nequal(const reference_arithmetic ref, Vector const& vect1, Vector const& vect2) {
  assert((vect1 != vect2) == ref.nequal(vect1, vect2));
}

void test_equal(const reference_arithmetic ref, Matrice const& mat, bool bit) {
  assert((mat == bit) == ref.equal(mat, bit));
}

void test_equal(const reference_arithmetic ref, Vector const& vect, bool bit) {
  assert((vect == bit) == ref.equal(vect, bit));
}
