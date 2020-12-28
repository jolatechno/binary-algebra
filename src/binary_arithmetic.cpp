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
#include "member/slice.inl"

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
  #ifdef MPIENABLED
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
  #endif
}

Matrix::Matrix(uint16_t _size) : height(_size), width(_size) {
  blocks = (uint64_t *) calloc(_size * _size, sizeof(uint64_t));
  if (blocks == NULL) throw std::bad_alloc();
  #ifdef MPIENABLED
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
  #endif
}

Vector::Vector(uint16_t _size): height(_size) {
  blocks = (uint8_t *) calloc(height, sizeof(uint64_t));
  if (blocks == NULL) throw std::bad_alloc();
  #ifdef MPIENABLED
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
  #endif
}


/*
copy operators
*/


Matrix::Matrix(Matrix const& other) : height(other.height), width(other.width) {
  blocks = (uint64_t *) calloc(height * width, sizeof(uint64_t)); //initialize empty blocks
  if (blocks == NULL) throw std::bad_alloc();
  #ifdef MPIENABLED
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
  #endif

  memcpy(blocks, other.blocks, height * width * sizeof(uint64_t)); //copy blocks
}

Vector::Vector(Vector const& other) : height(other.height) {
  blocks = (uint8_t *) calloc(height, sizeof(uint64_t)); //initialize empty blocks
  if (blocks == NULL) throw std::bad_alloc();
  #ifdef MPIENABLED
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
  #endif

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
