/*
slices operator
*/


matrix_slice Matrix::slice(int start_i, int start_j, int length_i, int length_j) {
  return matrix_slice(start_i, start_j, length_i, length_j, this);
}

vector_slice Vector::slice(int start, int length) {
  return vector_slice(start, length, this);
}


/*
slice cast operator
*/


matrix_slice::operator Matrix() const {
  Matrix res(length_i, length_j);

  for (int16_t i = 0; i < length_i; i++)
    memcpy(&res.blocks[i*length_j], &mat->blocks[start_j + (i + start_i)*mat->width], length_j * sizeof(uint64_t)); //copy blocks

  return res;
}

vector_slice::operator Vector() const {
  Vector res(length);

  memcpy(res.blocks, &vect->blocks[start], length * sizeof(uint8_t)); //copy blocks

  return res;
}


/*
slice assignment operators
*/


matrix_slice& matrix_slice::operator=(Matrix const& other) {
  assert(length_i == other.height);
  assert(length_j == other.width);

  for (int16_t i = 0; i < length_i; i++)
    memcpy(&mat->blocks[start_j + (i + start_i)*mat->width], &other.blocks[i*length_j], length_j * sizeof(uint64_t)); //copy blocks

  return *this;
}

vector_slice& vector_slice::operator=(Vector const& other) {
  assert(length == other.height);

  memcpy(&vect->blocks[start], other.blocks, length * sizeof(uint8_t)); //copy blocks

  return *this;
}

matrix_slice& matrix_slice::operator=(matrix_slice const& other) {
  assert(length_i == other.length_i);
  assert(length_j == other.length_j);

  for (int16_t i = 0; i < length_i; i++)
    memcpy(&mat->blocks[start_j + (i + start_i)*mat->width], &other.mat->blocks[other.start_j + (i + other.start_i)*other.mat->width], length_j * sizeof(uint64_t)); //copy blocks

  return *this;
}

#include <iostream>

vector_slice& vector_slice::operator=(vector_slice const& other) {
  assert(length == other.length);

  memcpy(&vect->blocks[start], &other.vect->blocks[other.start], length * sizeof(uint8_t)); //copy blocks

  return *this;
}
