#pragma once

#include <ostream>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

#include "utils/utils.hpp"

typedef class Matrix Matrix;
typedef class Vector Vector;

/*
slice struct
*/


struct vector_slice {
  Vector *vect;
  int start, length;

  //constructor
  vector_slice(int _start, int _length, Vector *_vect) : start(_start), length(_length), vect(_vect) {}

  operator Vector() const; //implicite comvertion
  vector_slice& operator=(Vector const& other); //assignment operators
  vector_slice& operator=(vector_slice const& other);
};

struct matrix_slice {
  Matrix *mat;
  int start_i, start_j, length_i, length_j;

  //constructor
  matrix_slice(int _start_i, int _start_j, int _length_i, int _length_j, Matrix *_mat) : start_i(_start_i), start_j(_start_j), length_i(_length_i), length_j(_length_j), mat(_mat) {}

  operator Matrix() const; //implicite comvertion
  matrix_slice& operator=(Matrix const& other); //assignment operators
  matrix_slice& operator=(matrix_slice const& other);
};


/*
assignment struct
*/


struct bool_from_byte {
  uint8_t *byte;
  int i;

  //util operations
  Utils* utils;

  //constructor
  bool_from_byte(int _i, uint8_t *_byte) : i(_i), byte(_byte) {}

  operator bool() const; //implicite comvertion
  bool_from_byte& operator=(bool value); //assignment operators
  bool_from_byte& operator=(bool_from_byte value) {
    *this = (bool)value;
    return *this;
  }
};

struct bool_from_word {
  uint64_t *word;
  int i, j;

  //util operations
  Utils* utils;

  //constructor
  bool_from_word(int _i, int _j, uint64_t *_word) : i(_i), j(_j), word(_word) {}

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
    inline uint64_t transpose_block(uint64_t const& block) const;
    inline uint8_t multiply_block_byte(uint64_t const& block, uint8_t const& vect) const;
    inline uint64_t multiply_block_block(uint64_t const& block_left, uint64_t const& block_right) const;

    #if defined(_OPENMP) && defined(TARGET)
      inline uint64_t multiply_block_word(uint64_t const& block0, uint64_t const& block1, uint64_t const& block2, uint64_t const& block3, \
        uint64_t const& block4, uint64_t const& block5, uint64_t const& block6, uint64_t const& block7, \
        uint8_t const& vect) const;
    #endif
    _OPENMP_GPU_PRAGMA("omp end declare target")

    //for comparaisons
    int difference(Matrix const& mat) const;

  public:
    //blocks
    uint64_t *blocks;

    //Stupid way of accessing Matrix elements, only for testing or debugging !
    bool_from_word operator()(int i, int j) const;

    //size
    const int height;
    const int width;

    //constructors
    Matrix(int mat_height, int mat_width);
    Matrix(int size);

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

    //slice
    matrix_slice slice(int start_i, int start_j, int length_i, int length_j);

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

    //gpu operations
    #if defined(_OPENMP) && defined(TARGET)
      void to();
      void to(int start, int length);
      void from();
      void from(int start, int length);
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
    inline uint64_t multiply_byte_byte(uint8_t const& vect_left, uint8_t const& vect_right) const;
    _OPENMP_GPU_PRAGMA("omp end declare target")

    //for comparaisons
    int difference(Vector const& vect) const;

  public:
    //blocks
    uint8_t *blocks;

    //Stupid way of accessing vector elements, only for testing or debugging !
    bool_from_byte operator[](int i) const;

    //size
    const int height;

    //constructor
    Vector(int size);

    //destructor
    ~Vector();

    //print operator
    friend std::ostream& operator<<(std::ostream& os, Vector const& vect);

    //copy and assignment operators
    Vector(Vector const& other);
    Vector& operator=(Vector const& other);

    //initializers
    void randomize();

    //slice
    vector_slice slice(int start, int length);

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

    //gpu operations
    #if defined(_OPENMP) && defined(TARGET)
      void to();
      void to(int start, int length);
      void from();
      void from(int start, int length);
    #endif
};
