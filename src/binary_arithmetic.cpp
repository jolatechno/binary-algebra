#include <new>
#include <stdlib.h>
#include <cassert>

#include "openmp.hpp"
#include "mpi.hpp"

#include "binary_arithmetic.hpp"
#include "reference_arithmetic/reference_arithmetic.hpp"

#include "member/read_write.inl"
#include "member/debug.inl"
#include "member/block_arithmetic.inl"

#include "mpi.inl"
#include "comparisons.inl"
#include "initializers.inl"
#include "arithmetic.inl"
#include "self_arithmetic.inl"

/*
constructors
*/


Matrix::Matrix(uint16_t mat_height, uint16_t mat_width) : height(mat_height), width(mat_width) {
  blocks = (uint64_t *) calloc(height * width, sizeof(uint64_t));
  if (blocks == NULL) throw std::bad_alloc();
}

Matrix::Matrix(uint16_t size) : height(size), width(size) {
  blocks = (uint64_t *) calloc(size * size, sizeof(uint64_t));
  if (blocks == NULL) throw std::bad_alloc();
}

Vector::Vector(uint16_t size): height(size) {
  blocks = (uint8_t *) calloc(height, sizeof(uint64_t));
  if (blocks == NULL) throw std::bad_alloc();
}


/*
copy operators
*/


Matrix::Matrix(Matrix const& other) : height(other.height), width(other.width) {
  blocks = (uint64_t *) calloc(height * width, sizeof(uint64_t)); //initialize empty blocks
  if (blocks == NULL) throw std::bad_alloc();

  memcpy(blocks, other.blocks, height * width * sizeof(uint64_t)); //copy blocks
}

Vector::Vector(Vector const& other) : height(other.height) {
  blocks = (uint8_t *) calloc(height, sizeof(uint64_t)); //initialize empty blocks
  if (blocks == NULL) throw std::bad_alloc();

  memcpy(blocks, other.blocks, height * sizeof(uint8_t)); //copy blocks
}


/*
destructors
*/


Matrix::~Matrix(){
  free(blocks);
}

Vector::~Vector(){
  free(blocks);
}
