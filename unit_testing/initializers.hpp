#pragma once

#include "../src/reference_arithmetic/reference_arithmetic.hpp"
#include "../src/binary_arithmetic.hpp"

#include <stdint.h>
#include <cassert>


/*
testing slices
*/
#include <iostream>


void test_slice(const reference_arithmetic ref, Matrix mat1, Matrix mat2) {
  Matrix stupid_slice = ref.slice(mat1, 1, 2, 3, 4);

  assert(ref.equal(mat1.slice(1, 2, 3, 4), stupid_slice));

  mat1.slice(1, 1, 2, 2) = mat2.slice(0, 1, 2, 2);
  assert(ref.equal(ref.slice(mat1, 1, 1, 2, 2), ref.slice(mat2, 0, 1, 2, 2)));

  mat1.slice(2, 2, 2, 2) = (Matrix)mat2.slice(1, 2, 2, 2);
  assert(ref.equal(ref.slice(mat1, 2, 2, 2, 2), ref.slice(mat2, 1, 2, 2, 2)));
}

void test_slice(const reference_arithmetic ref, Vector vect1, Vector vect2) {
  Vector stupid_slice = ref.slice(vect1, 1, 2);

  assert(ref.equal(vect1.slice(1, 2), stupid_slice));

  vect1.slice(2, 2) = vect2.slice(1, 2);
  assert(ref.equal(ref.slice(vect1, 2, 2), ref.slice(vect2, 1, 2)));

  vect1.slice(2, 2) = (Vector)vect2.slice(0, 2);
  assert(ref.equal(ref.slice(vect1, 2, 2), ref.slice(vect2, 0, 2)));
}


/*
testing zero initializer
*/


void test_zero_initalizer(const reference_arithmetic ref, int16_t height, int16_t width) {
  Matrix stupid_zero(height, width);
  ref.zero(stupid_zero);
  Matrix zero = Matrix(height, width);

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


void test_diag_initializer(const reference_arithmetic ref, Matrix& mat1, Matrix& mat2) {
  assert(mat1.height == mat2.height); //sufficient as mat1 and mat2 have to be square

  mat1.diag();
  ref.diag(mat2);

  assert(ref.equal(mat1, mat2));
}

void test_diag_initializer(const reference_arithmetic ref, Matrix& mat1, Matrix& mat2, Vector diagonal) {
  assert(mat1.height == mat2.height); //sufficient as mat1 and mat2 have to be square

  mat1.diag(diagonal);
  ref.diag(mat2, diagonal);

  assert(ref.equal(mat1, mat2));
}


/*
testing the random initializer
*/


void test_random(const reference_arithmetic ref, Matrix& mat, int16_t treshold) {
  bool failed_to_randomize = false;
  Matrix mat_copy(mat.height, mat.width);

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
