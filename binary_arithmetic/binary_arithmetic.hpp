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
    uint64_t transpose_block(uint64_t block) const;
    uint8_t multiply_block_byte(uint64_t block, uint8_t vect) const;
    uint64_t multiply_block_block(uint64_t block_left, uint64_t block_right) const;

    //for comparaisons
    int difference(Matrice const& mat) const;

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
    friend std::ostream& operator<<(std::ostream& os, Matrice const& mat);

    //copy and assignment operators
    Matrice(Matrice const& other);
    Matrice& operator=(Matrice const& other);

    //initializers
    void randomize();
    void diag();
    void diag(Vector const& diagonal);

    //comparaisons
    bool operator==(Matrice const& mat) const;
    bool operator==(const bool bit) const;
    bool operator!=(Matrice const& mat) const;
    bool operator!=(const bool bit) const;
    bool operator<(Matrice const& mat) const;
    bool operator<(const bool bit) const;
    bool operator>(Matrice const& mat) const;
    bool operator>(const bool bit) const;
    bool operator<=(Matrice const& mat) const;
    bool operator<=(const bool bit) const;
    bool operator>=(Matrice const& mat) const;
    bool operator>=(const bool bit) const;

    //self operators
    Matrice T() const;
    void operator^=(Matrice const& mat);
    void operator^=(const bool bit);
    void operator+=(Matrice const& mat); //aliases for the two previous
    void operator+=(const bool bit);
    void operator-=(Matrice const& mat); //also aliases for the two previous since addition and substraction mod2 are identical
    void operator-=(const bool bit);
    void operator&=(Matrice const& mat);
    void operator&=(const bool bit);
    void operator*=(Matrice const& mat);

    //operators
    Matrice operator~() const;
    bool operator%(Matrice const& mat) const; //scalar product
    int integer_scalar_product(Matrice const& mat) const; //integer scalar product
    Matrice operator^(Matrice const& mat) const;
    Matrice operator^(const bool bit) const;
    Matrice operator+(Matrice const& mat) const; //aliases for the two previous
    Matrice operator+(const bool bit) const;
    Matrice operator-(Matrice const& mat) const; //also aliases for the two previous since addition and substraction mod2 are identical
    Matrice operator-(const bool bit) const;
    Matrice operator&(Matrice const& mat) const;
    Matrice operator&(const bool bit) const;
    Vector operator*(Vector const& vect) const;
    Matrice operator*(Matrice const& mat) const;
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
    uint64_t multiply_byte_byte(uint8_t vect_left, uint8_t vect_right) const;

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
    void operator*=(Matrice const& mat);

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
    Matrice operator*(Vector const& vect) const;
};
