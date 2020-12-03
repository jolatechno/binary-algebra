#pragma once

#include "../binary_arithmetic/reference_arithmetic/reference_arithmetic.hpp"
#include "../binary_arithmetic/binary_arithmetic.hpp"

#include <stdint.h>
#include <cassert>


/*
testing zero initializer
*/


void test_zero_initalizer(const reference_arithmetic ref, int16_t height, int16_t width) {
  Matrice stupid_zero(height, width);
  ref.zero(stupid_zero);
  Matrice zero = Matrice(height, width);

  assert(ref.equal(zero, stupid_zero));
}

void test_zero_initalizer(const reference_arithmetic ref, int16_t height) {
  Vector stupid_zero(height);
  ref.zero(stupid_zero);
  Vector zero = Vector(height);

  assert(ref.equal(zero, stupid_zero));
}


/*
testing diag initializer
*/


void test_diag_initializer(const reference_arithmetic ref, Matrice& mat1, Matrice& mat2) {
  assert(mat1.height == mat2.height); //sufficient as mat1 and mat2 have to be square

  mat1.diag();
  ref.diag(mat2);

  assert(ref.equal(mat1, mat2));
}

void test_diag_initializer(const reference_arithmetic ref, Matrice& mat1, Matrice& mat2, Vector diagonal) {
  assert(mat1.height == mat2.height); //sufficient as mat1 and mat2 have to be square

  mat1.diag(diagonal);
  ref.diag(mat2, diagonal);

  assert(ref.equal(mat1, mat2));
}


/*
testing the random initializer
*/


void test_random(const reference_arithmetic ref, Matrice& mat, int16_t treshold) {
  bool failed_to_randomize = false;
  Matrice mat_copy(mat.height, mat.width);

  for (int16_t i = 0; i < treshold; i++) {
    mat_copy = mat;
    mat.randomize();
    if (!ref.equal(mat, mat_copy))
      return;
  }

  assert(failed_to_randomize);
}

void test_random(const reference_arithmetic ref, Vector& vect, int16_t treshold) {
  bool failed_to_randomize = false;
  Vector vect_copy(vect.height);

  for (int16_t i = 0; i < treshold; i++) {
    vect_copy = vect;
    vect.randomize();
    if (!ref.equal(vect, vect_copy))
      return;
  }

  assert(failed_to_randomize);
}
