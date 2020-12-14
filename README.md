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

Unit testing is supported by the `make test` directive, and compares result from the main arithmetic of this library, with the `reference_arithmetic` which uses trivial but slow algorithms.

"Typical" performance (on my average ryzen 3500u laptop, without killing any background task) is the following:

```console
joseph@pop-os:~/binary_algebra$ make clean performance_testing
rm -f **/*.out lib/*.a lib/*.o
g++ -std=c++0x -c binary_arithmetic/binary_arithmetic.cpp -o lib/binary_arithmetic.o -fopenmp
g++ -std=c++0x -c binary_arithmetic/utils/utils.cpp -o lib/utils.o -fopenmp
g++ -std=c++0x -c binary_arithmetic/reference_arithmetic/reference_arithmetic.cpp -o lib/reference_arithmetic.o -fopenmp
ar -crs lib/lib.a lib/binary_arithmetic.o lib/utils.o lib/reference_arithmetic.o
g++ -std=c++0x performance_testing/test.cpp lib/lib.a -o performance_testing/test.out -fopenmp
./performance_testing/test.out

Matrix transposition: 97.217000 µs/op for size=80bit
Matrix transposition: 240.617000 µs/op for size=800bit
Matrix transposition: 7.286927 ms/op for size=8000bit


Matrix equality: 253.000000 ns/op for size=80bit
Matrix equality: 13.219000 µs/op for size=800bit
Matrix equality: 8.186333 ms/op for size=8000bit

Vector equality: 412.000000 ns/op for size=80bit
Vector equality: 1.431000 µs/op for size=800bit
Vector equality: 55.040000 µs/op for size=8000bit


Matrix comparison: 287.000000 ns/op for size=80bit
Matrix comparison: 20.526000 µs/op for size=800bit
Matrix comparison: 7.725332 ms/op for size=8000bit

Vector comparison: 544.444000 µs/op for size=80bit
Vector comparison: 2.180000 µs/op for size=800bit
Vector comparison: 5.309000 µs/op for size=8000bit


Matrix addition: 2.324000 µs/op for size=80bit
Matrix addition: 181.582000 µs/op for size=800bit
Matrix addition: 8.776433 ms/op for size=8000bit

Vector addition: 247.311000 µs/op for size=80bit
Vector addition: 2.029000 µs/op for size=800bit
Vector addition: 2.979000 µs/op for size=8000bit


Matrix scalar product: 2.025000 µs/op for size=80bit
Matrix scalar product: 222.827000 µs/op for size=800bit
Matrix scalar product: 9.896874 ms/op for size=8000bit

Vector scalar product: 2.418000 µs/op for size=80bit
Vector scalar product: 1.812000 µs/op for size=800bit
Vector scalar product: 3.577000 µs/op for size=8000bit

Matrix integer scalar product: 34.306000 µs/op for size=80bit
Matrix integer scalar product: 1.375046 ms/op for size=800bit
Matrix integer scalar product: 10.946432 ms/op for size=8000bit

Vector integer scalar product: 418.199000 µs/op for size=80bit
Vector integer scalar product: 15.392000 µs/op for size=800bit
Vector integer scalar product: 2.157392 ms/op for size=8000bit


Vector multiplication with vector: 3.082737 ms/op for size=80bit
Vector multiplication with vector: 3.589747 ms/op for size=800bit
Vector multiplication with vector: 5.119671 ms/op for size=8000bit

Matrix multiplication with vector: 3.414911 ms/op for size=80bit
Matrix multiplication with vector: 3.230782 ms/op for size=800bit
Matrix multiplication with vector: 6.761850 ms/op for size=8000bit

Matrix multiplication with Matrix  342.376000 µs/op for size=80bit
Matrix multiplication with Matrix  7.791398 ms/op for size=800bit
Matrix multiplication with Matrix  24.690089 ms/op for size=8000bit
```

# Performance

Performance testing is supported by the

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
