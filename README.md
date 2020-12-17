# binary algebra

## What is "binary algebra" ?

Here what we mean by "binary algebra" is binary linear algebra - i.e. linear algebra inside of GF(2)^n (the [Galois field](https://en.wikipedia.org/wiki/GF(2)) of two elements - {0, 1}). In this space, we define the addition by the __xor__ operation, and the multiplication by the __and__ operation.

## How does this library work

### !! New matrix representation !!

Matrices and Vectors are stored as "blocks", byte for vectors and in64 word for matrices. A 64_bit word for a matrices represents a 8-by-8 bit block.

Up until now matrices were represented by block, with the indexing being similar inside and outside blocks - meaning that the (i, j) bit of a block, or block from a matrix, was the (j + i*weight)-th element of the linear representation of the matrix or block.

This now has changed, blocks are now store "transposed", which can be seen as reversing of the indexing of bit inside of blocks compared to the indexing of blocks inside of matrices.

This simplify some of the blocks operations (see [./binary_arithmetic/utils/block_arithmetic.inl](./binary_arithmetic/utils/block_arithmetic.inl)).

# Unit testing

Unit testing is supported by the `make test` directive which compares result from the main arithmetic of this library, with the `reference_arithmetic` which uses trivial but slow algorithms.

# Performance

Performance testing is supported by the `make performance_testing` directive which meusure the average time taken to apply some operation to varying size `Vectors` and `Matrices`.

"Typical" performances (on my average ryzen 3500u laptop, without killing any background task) are the following:

```console
joseph@pop-os:~/binary_algebra$ make clean performance_testing
g++ -std=c++0x -c binary_arithmetic/binary_arithmetic.cpp -o lib/binary_arithmetic.o -fopenmp
g++ -std=c++0x -c binary_arithmetic/utils/utils.cpp -o lib/utils.o -fopenmp
g++ -std=c++0x -c binary_arithmetic/reference_arithmetic/reference_arithmetic.cpp -o lib/reference_arithmetic.o -fopenmp
ar -crs lib/lib.a lib/binary_arithmetic.o lib/utils.o lib/reference_arithmetic.o
g++ -std=c++0x performance_testing/test.cpp lib/lib.a -o performance_testing/test.out -fopenmp
./performance_testing/test.out

Matrix transposition: 3.627000 µs/op for size=80bit
Matrix transposition: 297.302000 µs/op for size=800bit
Matrix transposition: 4.632472 ms/op for size=8000bit


Matrix equality: 234.000000 ns/op for size=80bit
Matrix equality: 10.006000 µs/op for size=800bit
Matrix equality: 6.671043 ms/op for size=8000bit

Vector equality: 278.000000 ns/op for size=80bit
Vector equality: 1.385000 µs/op for size=800bit
Vector equality: 12.190000 µs/op for size=8000bit


Matrix comparison: 245.000000 ns/op for size=80bit
Matrix comparison: 10.165000 µs/op for size=800bit
Matrix comparison: 6.558593 ms/op for size=8000bit

Vector comparison: 1.653000 µs/op for size=80bit
Vector comparison: 2.691000 µs/op for size=800bit
Vector comparison: 11.420000 µs/op for size=8000bit


Matrix addition: 3.394000 µs/op for size=80bit
Matrix addition: 283.475000 µs/op for size=800bit
Matrix addition: 5.718697 ms/op for size=8000bit

Vector addition: 1.357000 µs/op for size=80bit
Vector addition: 1.671000 µs/op for size=800bit
Vector addition: 2.708000 µs/op for size=8000bit


Matrix scalar product: 2.144000 µs/op for size=80bit
Matrix scalar product: 34.079000 µs/op for size=800bit
Matrix scalar product: 7.165217 ms/op for size=8000bit

Vector scalar product: 1.603000 µs/op for size=80bit
Vector scalar product: 1.898000 µs/op for size=800bit
Vector scalar product: 3.790000 µs/op for size=8000bit

Matrix integer scalar product: 6.331000 µs/op for size=80bit
Matrix integer scalar product: 547.217000 µs/op for size=800bit
Matrix integer scalar product: 7.975569 ms/op for size=8000bit

Vector integer scalar product: 1.674000 µs/op for size=80bit
Vector integer scalar product: 2.205000 µs/op for size=800bit
Vector integer scalar product: 6.421000 µs/op for size=8000bit


Vector multiplication with vector: 4.015000 µs/op for size=80bit
Vector multiplication with vector: 306.866000 µs/op for size=800bit
Vector multiplication with vector: 1.796962 ms/op for size=8000bit

Matrix multiplication with vector: 3.910000 µs/op for size=80bit
Matrix multiplication with vector: 166.233000 µs/op for size=800bit
Matrix multiplication with vector: 3.269260 ms/op for size=8000bit

Matrix multiplication with Matrix  389.901000 µs/op for size=80bit
Matrix multiplication with Matrix  3.172075 ms/op for size=800bit
Matrix multiplication with Matrix  19.388963 ms/op for size=8000bit
```

# Supported operations

## Printing

You can "print" a `Vector` or a `Matrix` using the following code :

```cpp
//binary_arithmetic included earlier
#include <iostream>

int main(int argc, char** argv){
  Matrix mat(2, 2);
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
