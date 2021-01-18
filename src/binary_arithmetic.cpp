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
#include "openmp.inl"
#include "comparisons.inl"
#include "initializers.inl"
#include "arithmetic.inl"
#include "self_arithmetic.inl"

/*
constructors
*/


Matrix::Matrix(int _height, int _width) : height(_height), width(_width) {
  blocks = (uint64_t *) calloc(height * width, sizeof(uint64_t));
  if (blocks == NULL) throw std::bad_alloc();
  #ifdef MPIENABLED
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
  #endif
  #if defined(_OPENMP) && defined(TARGET)
    uint64_t *this_blocks = blocks;
    #pragma omp target enter data map(alloc:this_blocks[:_height * _width])
  #endif
}

Matrix::Matrix(int _size) : height(_size), width(_size) {
  blocks = (uint64_t *) calloc(_size * _size, sizeof(uint64_t));
  if (blocks == NULL) throw std::bad_alloc();
  #ifdef MPIENABLED
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
  #endif
  #if defined(_OPENMP) && defined(TARGET)
    uint64_t *this_blocks = blocks;
    #pragma omp target enter data map(alloc:this_blocks[:_size * _size])
  #endif
}

Vector::Vector(int _size): height(_size) {
  blocks = (uint8_t *) calloc(height, sizeof(uint64_t));
  if (blocks == NULL) throw std::bad_alloc();
  #ifdef MPIENABLED
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
  #endif
  #if defined(_OPENMP) && defined(TARGET)
    uint8_t *this_blocks = blocks;
    #pragma omp target enter data map(alloc:this_blocks[:_size])
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

  #if defined(_OPENMP) && defined(TARGET)
    int _size = height * width;
    uint64_t *this_blocks = blocks;
    #pragma omp target enter data map(to:this_blocks[:_size])
  #endif
}

Vector::Vector(Vector const& other) : height(other.height) {
  blocks = (uint8_t *) calloc(height, sizeof(uint64_t)); //initialize empty blocks
  if (blocks == NULL) throw std::bad_alloc();
  #ifdef MPIENABLED
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
  #endif

  memcpy(blocks, other.blocks, height * sizeof(uint8_t)); //copy blocks

  #if defined(_OPENMP) && defined(TARGET)
    int _height = height;
    uint8_t *this_blocks = blocks;
    #pragma omp target enter data map(to:this_blocks[:_height])
  #endif
}


/*
destructors
*/


Matrix::~Matrix(){
  #if defined(_OPENMP) && defined(TARGET)
    int _size = height * width;
    uint64_t *this_blocks = blocks;
    #pragma omp target exit data map(release:this_blocks[:_size])
  #endif
  free(blocks);
}

Vector::~Vector(){
  #if defined(_OPENMP) && defined(TARGET)
    int _height = height;
    uint8_t *this_blocks = blocks;
    #pragma omp target exit data map(release:this_blocks[:_height])
  #endif
  free(blocks);
}
