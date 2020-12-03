#include <new>

#include "binary_arithmetic.hpp"
#include "reference_arithmetic/reference_arithmetic.hpp"

#include "comparaisons.inl"
#include "initializers.inl"
#include "arithmetic.inl"
#include "self_arithmetic.inl"

#include "reference_arithmetic/read_write.inl"

#include "utils/debug.inl"
#include "utils/block_arithmetic.inl"

/*
constructors
*/


Matrice::Matrice(uint16_t mat_height, uint16_t mat_width) : height(mat_height), width(mat_width) {
  blocks = (uint64_t *) calloc(height * width, sizeof(uint64_t));
  if (blocks == NULL) throw std::bad_alloc();
}

Matrice::Matrice(uint16_t size) : height(size), width(size) {
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


Matrice::Matrice(const Matrice& other) : height(other.height), width(other.width) {
  blocks = (uint64_t *) calloc(height * width, sizeof(uint64_t)); //initialize empty blocks
  if (blocks == NULL) throw std::bad_alloc();

  memcpy(blocks, other.blocks, height * width * sizeof(uint64_t)); //copy blocks
}

Vector::Vector(const Vector& other) : height(other.height) {
  blocks = (uint8_t *) calloc(height, sizeof(uint64_t)); //initialize empty blocks
  if (blocks == NULL) throw std::bad_alloc();

  memcpy(blocks, other.blocks, height * sizeof(uint8_t)); //copy blocks
}


/*
destructors
*/


Matrice::~Matrice(){
  //free(blocks); //todo
}

Vector::~Vector(){
  //free(blocks); //todo
}
