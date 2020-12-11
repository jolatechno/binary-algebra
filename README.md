# binary algebra

## What is "binary algebra" ?

Here what we mean by "binary algebra" is binary linear algebra - i.e. linear algebra inside of GF(2)^n (the [Galois field](https://en.wikipedia.org/wiki/GF(2)) of two elements - {0, 1}). In this space, we define the addition by the __xor__ operation, and the multiplication by the __and__ operation.

## How does this library work

### !! New matrix representation !!

Matrices and Vectors are stored as "blocks", byte for vectors and in64 word for matrices. A 64_bit word for a matrices represents a 8-by-8 bit block.

Up until now matrices were represented by block, with the indexing being similar inside and outside blocks - meaning that the (i, j) bit of a block, or block from a matrix, was the (j + i*weight)-th element of the linear representation of the matrix or block.

This now has changed, blocks are now store "transposed", which can be seen as reversing of the indexing of bit inside of blocks compared to the indexing of blocks inside of matrices.

This simplify some of the blocks operations (see [./binary_arithmetic/utils/block_arithmetic.inl](./binary_arithmetic/utils/block_arithmetic.inl)).

# Supported operations

## Printing

You can "print" a `Vector` or `Matrice` using the following code :

```cpp
//binary_arithmetic included earlier
#include <iostream>

int main(int argc, char** argv){
  Matrice mat(2, 2);
  Vector vect(2);
  std::cout << mat << "\n" << vect;
}
```

## Arithmetic

### Addition, subtraction and xor

Mod-2 bitwise addition (and subtraction and "xor" which are similar), respectively noted `+, -, ^`, are supported between `Vectors` or `Matrices` of similar size, or between `Vectors` and `Matrices` and a `bit` (of type `bool`).

### Bitwise multiplication

Bitwise multiplication (or "and" which is similar), noted `&`, is supported between `Vectors` or `Matrices` of similar size, or between `Vectors` and `Matrices` and a `bit` (of type `bool`).

### Matrix multiplication

Matrix multiplication is supported between `Vectors` or `Matrices` (if the shapes are compatible), and is noted `*`.

### Matrix transposition

the `M.T()` operator returns the transposition of the `M` Matrix.

### Negation

`Vectors` and `Matrices` can be negated by using the negation operator noted `~`.

### Scalar product

Mod-2 usual scalar product is supported between `Vectors` or `Matrices` of similar size, and is noted `&`.

### Integer scalar product

The usual scalar product is supported between `Vectors` or `Matrices` of similar size, and returns the number of ones in the bitwise multiplication between the two `Vectors` or `Matrices`. This scalar product is called by the function `X.integer_scalar_product(other)`.


## Comparisons

### Equality and Inequality

Equality and Inequality, respectively noted `==` and `!=`, is supported between `Vectors` or `Matrices` of similar size.

### Strict and wide inequalities

Strict and wide inequalities are supported between `Vectors` or `Matrices` of similar size, and are implemented by comparing the number of ones in both object. Supported inequalities are the following: `<, >, <=, >=`.

## Self arithmetic

All the previous operations are supported as a "self operator" (the "self operator" supported are the following:  `+=, ^=, -=, &=, *=`)
