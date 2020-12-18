#pragma once

#include <ostream>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <cassert>
#include <stdbool.h>

#include "utils/utils.hpp"

typedef class Matrix Matrix;
typedef class Vector Vector;

class Matrix {
  friend Vector;
  friend class reference_arithmetic;

  private:
    //blocks
    uint64_t *blocks;

    //util operations
    Utils* utils;

    //block operations
    inline uint64_t transpose_block(uint64_t block) const;
    inline uint8_t multiply_block_byte(uint64_t block, uint8_t vect) const;
    inline uint64_t multiply_block_block(uint64_t block_left, uint64_t block_right) const;

    //for comparaisons
    int difference(Matrix const& mat) const;

    //Stupid way of accessing Matrix elements, only for testing or debugging !
    bool operator()(uint16_t i, uint16_t j) const;
    void write(uint16_t i, uint16_t j, bool bit);

  public:
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
    int integer_scalar_product(Matrix const& mat) const; //integer scalar product
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
};

class Vector {
  friend Matrix;
  friend class reference_arithmetic;

  private:
    //blocks
    uint8_t *blocks;

    //util operations
    Utils* utils;

    //block operations
    inline uint64_t multiply_byte_byte(uint8_t vect_left, uint8_t vect_right) const;

    //for comparaisons
    int difference(Vector const& vect) const;

    //Stupid way of accessing vector elements, only for testing or debugging !
    bool operator[](uint16_t i) const;
    void write(uint16_t i, bool bit);

  public:
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
    int integer_scalar_product(Vector const& vect) const; //integer scalar product
    Vector operator^(Vector const& vect) const;
    Vector operator^(const bool bit) const;
    Vector operator+(Vector const& vect) const; //aliases for the two previous
    Vector operator+(const bool bit) const;
    Vector operator-(Vector const& vect) const; //also aliases for the two previous since addition and substraction mod2 are identical
    Vector operator-(const bool bit) const;
    Vector operator&(Vector const& vect) const;
    Vector operator&(const bool bit) const;
    Matrix operator*(Vector const& vect) const;
};
