#pragma once

#include <stdint.h>
#include <cassert>
#include <stdbool.h>

#include "../binary_arithmetic.hpp"

typedef class reference_arithmetic reference_arithmetic;
class Matrice;
class Vector;

class reference_arithmetic {
  friend class Matrice;
  friend class Vector;

  public:
    //transposition
    Matrice transpose(Matrice const& mat) const;

    //multiplications
    Matrice multiplication(Matrice const& mat1, Matrice const& mat2) const;
    Vector multiplication(Matrice const& mat, Vector const& vect) const;
    Matrice multiplication(Vector const& vect1, Vector const& vect2) const;

    //additions
    Matrice addition(Matrice const& mat1, Matrice const& mat2) const;
    Matrice addition(Matrice const& mat, bool bit) const;
    Vector addition(Vector const& vect1, Vector const& vect2) const;
    Vector addition(Vector const& vect, bool bit) const;

    //bitwise multiplication
    Matrice bitwise_multiplication(Matrice const& mat1, Matrice const& mat2) const;
    Matrice bitwise_multiplication(Matrice const& mat, bool bit) const;
    Vector bitwise_multiplication(Vector const& vect1, Vector const& vect2) const;
    Vector bitwise_multiplication(Vector const& vect, bool bit) const;

    //negation
    Matrice negate(Matrice const& mat) const;
    Vector negate(Vector const& vect) const;


    //scalar product
    bool scalar_product(Matrice const& mat1, Matrice const& mat2) const;
    bool scalar_product(Vector const& vect1, Vector const& vect2) const;
    int integer_scalar_product(Matrice const& mat1, Matrice const& mat2) const;
    int integer_scalar_product(Vector const& vect1, Vector const& vect2) const;

    //comparaisons
    bool equal(Matrice const& mat1, Matrice const& mat2) const;
    bool equal(Vector const& vect1, Vector const& vect2) const;
    bool nequal(Matrice const& mat1, Matrice const& mat2) const;
    bool nequal(Vector const& vect1, Vector const& vect2) const;
    bool equal(Matrice const& mat1, bool bit) const;
    bool equal(Vector const& vect, bool bit) const;

    //initializers
    void zero(Matrice& mat) const;
    void zero(Vector& vect) const;
    void diag(Matrice& mat) const;
    void diag(Matrice& mat, Vector const& diagonal) const;
};
