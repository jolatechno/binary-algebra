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
    Matrice transpose(const Matrice mat) const;

    //multiplications
    Matrice multiplication(const Matrice mat1, const Matrice mat2) const;
    Vector multiplication(const Matrice mat, const Vector vect) const;
    Matrice multiplication(const Vector vect1, const Vector vect2) const;

    //additions
    Matrice addition(const Matrice mat1, const Matrice mat2) const;
    Matrice addition(const Matrice mat, bool bit) const;
    Vector addition(const Vector vect1, const Vector vect2) const;
    Vector addition(const Vector vect, bool bit) const;

    //bitwise multiplication
    Matrice bitwise_multiplication(const Matrice mat1, const Matrice mat2) const;
    Matrice bitwise_multiplication(const Matrice mat, bool bit) const;
    Vector bitwise_multiplication(const Vector vect1, const Vector vect2) const;
    Vector bitwise_multiplication(const Vector vect, bool bit) const;

    //negation
    Matrice negate(const Matrice mat) const;
    Vector negate(const Vector vect) const;


    //scalar product
    bool scalar_product(const Matrice mat1, const Matrice mat2) const;
    bool scalar_product(const Vector vect1, const Vector vect2) const;

    //comparaisons
    bool equal(const Matrice mat1, const Matrice mat2) const;
    bool equal(const Vector vect1, const Vector vect2) const;
    bool nequal(const Matrice mat1, const Matrice mat2) const;
    bool nequal(const Vector vect1, const Vector vect2) const;
    bool equal(const Matrice mat1, bool bit) const;
    bool equal(const Vector vect, bool bit) const;

    //initializers
    void zero(Matrice mat) const;
    void zero(Vector vect) const;
    void diag(Matrice& mat) const;
    void diag(Matrice& mat, const  Vector diagonal) const;
};
