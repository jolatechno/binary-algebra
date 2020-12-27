#pragma once

#include <ostream>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

#include "utils/utils.hpp"

typedef class Matrix Matrix;
typedef class Vector Vector;


/*
assignment struct
*/


struct bool_from_byte {
  uint8_t *byte;
  uint16_t i;

  //util operations
  Utils* utils;

  //constructor
  bool_from_byte(int16_t _i, uint8_t *_byte) : i(_i), byte(_byte) {}

  operator bool() const; //implicite comvertion
  bool_from_byte& operator=(bool value); //assignment operators
  bool_from_byte& operator=(bool_from_byte value) {
    *this = (bool)value;
    return *this;
  }
};

struct bool_from_word {
  uint64_t *word;
  uint16_t i, j;

  //util operations
  Utils* utils;

  //constructor
  bool_from_word(int16_t _i, int16_t _j, uint64_t *_word) : i(_i), j(_j), word(_word) {}

  operator bool() const; //implicite comvertion
  bool_from_word& operator=(bool value); //assignment operators
  bool_from_word& operator=(bool_from_word value) {
    *this = (bool)value;
    return *this;
  }
};


/*
classes
*/


class Matrix {
  friend Vector;

  private:
    //mpi variables
    #ifdef MPIENABLED
      int num_workers = 1; //number of mpi worker
      int rank, size;
    #endif

    //util operations
    Utils* utils;

    //block operations
    _OPENMP_GPU_PRAGMA("omp declare target")
    inline uint64_t transpose_block(uint64_t block) const;
    inline uint8_t multiply_block_byte(uint64_t block, uint8_t vect) const;
    inline uint64_t multiply_block_word(uint64_t block0, uint64_t block1, uint64_t block2, uint64_t block3, \
      uint64_t block4, uint64_t block5, uint64_t block6, uint64_t block7, \
      uint8_t vect) const;
    inline uint64_t multiply_block_block(uint64_t block_left, uint64_t block_right) const;
    _OPENMP_GPU_PRAGMA("omp end declare target")

    //for comparaisons
    int difference(Matrix const& mat) const;

  public:
    //blocks
    uint64_t *blocks;

    //Stupid way of accessing Matrix elements, only for testing or debugging !
    bool_from_word operator()(uint16_t i, uint16_t j) const;

    //size
    const uint16_t height;
    const uint16_t width;

    //constructors
    Matrix(uint16_t mat_height, uint16_t mat_width);
    Matrix(uint16_t size);

    //destructor
    ~Matrix();

    //print operator
    friend std::ostream& operator<<(std::ostream& os, Matrix const& mat);

    //copy and assignment operators
    Matrix(Matrix const& other);
    Matrix& operator=(Matrix const& other);

    //initializers
    void randomize();
    void diag();
    void diag(Vector const& diagonal);

    //comparaisons
    bool operator==(Matrix const& mat) const;
    bool operator==(const bool bit) const;
    bool operator!=(Matrix const& mat) const;
    bool operator!=(const bool bit) const;
    bool operator<(Matrix const& mat) const;
    bool operator<(const bool bit) const;
    bool operator>(Matrix const& mat) const;
    bool operator>(const bool bit) const;
    bool operator<=(Matrix const& mat) const;
    bool operator<=(const bool bit) const;
    bool operator>=(Matrix const& mat) const;
    bool operator>=(const bool bit) const;

    //self operators
    Matrix T() const;
    void operator^=(Matrix const& mat);
    void operator^=(const bool bit);
    void operator+=(Matrix const& mat); //aliases for the two previous
    void operator+=(const bool bit);
    void operator-=(Matrix const& mat); //also aliases for the two previous since addition and substraction mod2 are identical
    void operator-=(const bool bit);
    void operator&=(Matrix const& mat);
    void operator&=(const bool bit);
    void operator*=(Matrix const& mat);

    //operators
    Matrix operator~() const;
    bool operator%(Matrix const& mat) const; //scalar product
    int operator/(Matrix const& mat) const; //integer scalar product
    Matrix operator^(Matrix const& mat) const;
    Matrix operator^(const bool bit) const;
    Matrix operator+(Matrix const& mat) const; //aliases for the two previous
    Matrix operator+(const bool bit) const;
    Matrix operator-(Matrix const& mat) const; //also aliases for the two previous since addition and substraction mod2 are identical
    Matrix operator-(const bool bit) const;
    Matrix operator&(Matrix const& mat) const;
    Matrix operator&(const bool bit) const;
    Vector operator*(Vector const& vect) const;
    Matrix operator*(Matrix const& mat) const;

    //mpi operation
    #ifdef MPIENABLED
      void set_pool_size(int num_workers);
      int send(int to) const;
      int send(int to, int start_i, int start_j, int length_i, int length_j) const;
      int receive(int from);
      int receive(int from, int start_i, int start_j, int length_i, int length_j);
    #endif
};

class Vector {
  friend Matrix;

  private:
    //mpi variables
    #ifdef MPIENABLED
      int num_workers = 1; //number of mpi worker
      int rank, size;
    #endif

    //util operations
    Utils* utils;

    //block operations
    _OPENMP_GPU_PRAGMA("omp declare target")
    inline uint64_t multiply_byte_byte(uint8_t vect_left, uint8_t vect_right) const;
    _OPENMP_GPU_PRAGMA("omp end declare target")

    //for comparaisons
    int difference(Vector const& vect) const;

  public:
    //blocks
    uint8_t *blocks;

    //Stupid way of accessing vector elements, only for testing or debugging !
    bool_from_byte operator[](uint16_t i) const;

    //size
    const uint16_t height;

    //constructor
    Vector(uint16_t size);

    //destructor
    ~Vector();

    //print operator
    friend std::ostream& operator<<(std::ostream& os, Vector const& vect);

    //copy and assignment operators
    Vector(Vector const& other);
    Vector& operator=(Vector const& other);

    //initializers
    void randomize();

    //comparaisons
    bool operator==(Vector const& vect) const;
    bool operator==(const bool bit) const;
    bool operator!=(Vector const& vect) const;
    bool operator!=(const bool bit) const;
    bool operator<(Vector const& vect) const;
    bool operator<(const bool bit) const;
    bool operator>(Vector const& vect) const;
    bool operator>(const bool bit) const;
    bool operator<=(Vector const& vect) const;
    bool operator<=(const bool bit) const;
    bool operator>=(Vector const& vect) const;
    bool operator>=(const bool bit) const;

    //self operators
    void operator^=(Vector const& vect);
    void operator^=(const bool bit);
    void operator+=(Vector const& vect); //aliases for the two previous
    void operator+=(const bool bit);
    void operator-=(Vector const& vect); //also aliases for the two previous since addition and substraction mod2 are identical
    void operator-=(const bool bit);
    void operator&=(Vector const& vect);
    void operator&=(const bool bit);
    void operator*=(Matrix const& mat);

    //operators
    Vector operator~() const;
    bool operator%(Vector const& vect) const; //scalar product
    int operator/(Vector const& vect) const; //integer scalar product
    Vector operator^(Vector const& vect) const;
    Vector operator^(const bool bit) const;
    Vector operator+(Vector const& vect) const; //aliases for the two previous
    Vector operator+(const bool bit) const;
    Vector operator-(Vector const& vect) const; //also aliases for the two previous since addition and substraction mod2 are identical
    Vector operator-(const bool bit) const;
    Vector operator&(Vector const& vect) const;
    Vector operator&(const bool bit) const;
    Matrix operator*(Vector const& vect) const;

    //mpi operation
    #ifdef MPIENABLED
      void set_pool_size(int num_workers);
      int send(int to) const;
      int send(int to, int start, int length) const;
      int receive(int from);
      int receive(int from, int start, int length);
    #endif
};
