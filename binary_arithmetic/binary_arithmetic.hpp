#pragma once

#include <ostream>
#include <stdint.h>
#include <stdlib.h>
#include <omp.h>
#include <string.h>
#include <cassert>
#include <stdbool.h>

#include "utils/utils.hpp"

typedef class Matrice Matrice;
typedef class Vector Vector;

class Matrice {
  friend Vector;
  friend class reference_arithmetic;

  private:
    //blocks
    uint64_t *blocks;

    //util operations
    Utils* utils;

    //block operations
    bool count_ones_64_mod2(uint64_t word) const;
    uint64_t transpose_block(uint64_t block) const;
    uint8_t multiply_block_byte(uint64_t block, uint8_t vect) const;
    uint64_t multiply_block_block(uint64_t block_left, uint64_t block_right) const;

    //Stupid way of accessing matrice elements, only for testing or debugging !
    bool operator()(uint16_t i, uint16_t j) const;
    void write(uint16_t i, uint16_t j, bool bit);

  public:
    //size
    const uint16_t height;
    const uint16_t width;

    //constructors
    Matrice(uint16_t mat_height, uint16_t mat_width);
    Matrice(uint16_t size);

    //destructor
    ~Matrice();

    //print operator
    friend std::ostream& operator<<(std::ostream& os, const Matrice& mat);

    //copy and assignment operators
    Matrice(const Matrice& other);
    Matrice& operator=(const Matrice other);

    //initializers
    void randomize();
    void diag();
    void diag(const Vector diagonal);

    //comparaisons
    bool operator==(const Matrice vect) const;
    bool operator!=(const Matrice vect) const;
    bool operator==(const bool bit) const;

    //self operators
    Matrice T() const;
    void operator^=(const Matrice mat);
    void operator^=(const bool bit);
    void operator&=(const Matrice mat);
    void operator&=(const bool bit);
    void operator*=(const Matrice mat);

    //operators
    Matrice operator~() const;
    bool operator%(const Matrice mat) const; //scalar product
    Matrice operator^(const Matrice mat) const;
    Matrice operator^(const bool bit) const;
    Matrice operator&(const Matrice mat) const;
    Matrice operator&(const bool bit) const;
    Vector operator*(const Vector vect) const;
    Matrice operator*(const Matrice mat) const;
};

class Vector {
  friend Matrice;
  friend class reference_arithmetic;

  private:
    //blocks
    uint8_t *blocks;

    //util operations
    Utils* utils;

    //block operations
    bool count_ones_8_mod2(uint8_t byte) const;
    uint64_t multiply_byte_byte(uint8_t vect_left, uint8_t vect_right) const;

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
    friend std::ostream& operator<<(std::ostream& os, const Vector& vect);

    //copy and assignment operators
    Vector(const Vector& other);
    Vector& operator=(const Vector other);

    //initializers
    void randomize();

    //comparaisons
    bool operator==(const Vector vect) const;
    bool operator!=(const Vector vect) const;
    bool operator==(const bool bit) const;

    //self operators
    void operator^=(const Vector vect);
    void operator^=(const bool bit);
    void operator&=(const Vector vect);
    void operator&=(const bool bit);
    void operator*=(const Matrice mat);

    //operators
    Vector operator~() const;
    bool operator%(const Vector vect) const; //scalar product
    Vector operator^(const Vector vect) const;
    Vector operator^(const bool bit) const;
    Vector operator&(const Vector vect) const;
    Vector operator&(const bool bit) const;
    Matrice operator*(const Vector vect) const;
};
