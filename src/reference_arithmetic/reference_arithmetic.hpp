#pragma once

#include <stdint.h>
#include <cassert>
#include <stdbool.h>

#include "../binary_arithmetic.hpp"

typedef class reference_arithmetic reference_arithmetic;
class Matrix;
class Vector;

class reference_arithmetic {
  public:
    //transposition
    Matrix transpose(Matrix const& mat) const;

    //multiplications
    Matrix multiplication(Matrix const& mat1, Matrix const& mat2) const;
    Vector multiplication(Matrix const& mat, Vector const& vect) const;
    Matrix multiplication(Vector const& vect1, Vector const& vect2) const;

    //additions
    Matrix addition(Matrix const& mat1, Matrix const& mat2) const;
    Matrix addition(Matrix const& mat, bool bit) const;
    Vector addition(Vector const& vect1, Vector const& vect2) const;
    Vector addition(Vector const& vect, bool bit) const;

    //bitwise multiplication
    Matrix bitwise_multiplication(Matrix const& mat1, Matrix const& mat2) const;
    Matrix bitwise_multiplication(Matrix const& mat, bool bit) const;
    Vector bitwise_multiplication(Vector const& vect1, Vector const& vect2) const;
    Vector bitwise_multiplication(Vector const& vect, bool bit) const;

    //negation
    Matrix negate(Matrix const& mat) const;
    Vector negate(Vector const& vect) const;


    //scalar product
    bool scalar_product(Matrix const& mat1, Matrix const& mat2) const;
    bool scalar_product(Vector const& vect1, Vector const& vect2) const;
    int integer_scalar_product(Matrix const& mat1, Matrix const& mat2) const;
    int integer_scalar_product(Vector const& vect1, Vector const& vect2) const;

    //comparaisons
    bool equal(Matrix const& mat1, Matrix const& mat2) const;
    bool equal(Vector const& vect1, Vector const& vect2) const;
    bool greater(Matrix const& mat1, Matrix const& mat2) const;
    bool greater(Vector const& vect1, Vector const& vect2) const;
    bool equal(Matrix const& mat1, bool bit) const;
    bool equal(Vector const& vect, bool bit) const;

    //initializers
    void zero(Matrix& mat) const;
    void zero(Vector& vect) const;
    void diag(Matrix& mat) const;
    void diag(Matrix& mat, Vector const& diagonal) const;

    //slices
    Matrix slice(Matrix mat, int start_i, int start_j, int length_i, int length_j) const;
    Vector slice(Vector vect, int start, int length) const;
};
