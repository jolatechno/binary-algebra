# binary algebra

## Requirements

This library is design for Linux only _for now_. For the best result, you should install __Openmp__ (`libomp5-xx`), and compile the library using it.

For GPU offloading you will also need the correct GPU drivers, `nvptx-tools` and `gcc-offload-nvptx`.

## Compilation

To compile this library without __Openmp__ simply use `make lib.a`, and you will find the `lib.a` library file in the [./lib](./lib) folder.

### Openmp

To compile it with __Openmp__, you need to use the `"openmp"` directive before all other targets, which will modify the `LDLIBS` variable in the [Makefile](./Makefile).

### Offloading to GPUs

To compile it with __Openmp__ and enable Offlowding to GPUs, you will need to use the `"gpu"` directive before all other targets, which will modify the `CCFLAGS` and `LDLIBS` variable in the [Makefile](./Makefile).

All arithmetic operations, self-operators, and comparisons excluding `==, !=` (for performance reasons) are now supported on GPUs.

Atomic operations for type `uint8_t` are not supported by __Openmp__ on GPU (see [issue #1](https://github.com/jolatechno/binary_algebra/issues/1)). I finally found a work around for every operation, either by converting types, or by grouping operations together to only apply atomic operations on `long unsigned int`.

I will implement threshold for which will redirect operation to the CPU without __Openmp__, the CPU with __Openmp__, or GPUs; according to the size of the `Matrix` or `Vector`.

## What is "binary algebra" ?

Here what we mean by "binary algebra" is binary linear algebra - i.e. linear algebra inside of GF(2)^n (the [Galois field](https://en.wikipedia.org/wiki/GF(2)) of two elements - {0, 1}). In this space, we define the addition by the __xor__ operation, and the multiplication by the __and__ operation.

## How does this library work

### !! New matrix representation !!

Matrices and Vectors are stored as "blocks", byte for vectors and in64 word for matrices. A 64_bit word for a matrices represents a 8-by-8 bit block.

Up until now matrices were represented by block, with the indexing being similar inside and outside blocks - meaning that the (i, j) bit of a block, or block from a matrix, was the (j + i*weight)-th element of the linear representation of the matrix or block.

This now has changed, blocks are now store "transposed", which can be seen as reversing of the indexing of bit inside of blocks compared to the indexing of blocks inside of matrices.

This simplify some of the blocks operations (see [./src/member/block_arithmetic.inl](./src/member/block_arithmetic.inl)).

# Unit testing

Unit testing is supported by the `make test` directive which compares result from the main arithmetic of this library, with the `reference_arithmetic` which uses trivial but slow algorithms.

# Performance

Performance testing is supported by the `make performance_testing` directive which meusure the average time taken to apply some operation to varying size `Vectors` and `Matrices`.

"Typical" performances are the following:

| Objects | Operation | Time (ryzen 3550U)<br>With Openmp | Time (ryzen 3550U)<br>Without Openmp |
| ------- | --------- | --------------------------------- | ------------------------------------ |
| Matrix-800bit | .T() | 225 µs/op | 201 µs/op |
| Vectors-800bit<br>Matrix-800bit | +, -, &, ^ | 1.9 µs/op<br>69 µs/op | 216 ns/op<br>63 µs/op |
| Vectors-800bit<br>Matrix-800bit | ==, != | 1.3 µs/op<br>10 µs/op |  115 ns/op<br>14 µs/op |
| Vectors-800bit<br>Matrix-800bit | <, >, <=, >= | 2.3 µs/op<br>9.8 µs/op | 1.4 µs/op<br>14 µs/op |
| Vectors-800bit<br>Matrix-800bit | / | 2 µs/op<br>310 µs/op | 842 ns/op<br>816 µs/op |
| Vectors-800bit<br>Matrix-800bit | % | 12 µs/op<br>39 µs/op | 410 ns/op<br>44 µs/op |
| Vectors-800bit | * | 149 µs/op | 346 µs/op |
| Matrix-800bit Vectors-800bit | * | 222 µs/op | 679 µs/op |
| Matrix-800bit | * | 2 ms/op | 556 ms/op |

We can see that the __Openmp__ version is much faster for multiplication, and mostly similar with other operations. This behavior would also be seen for almost all other operation with size greater than 2000bit. Some optimization might be due on the __Openmp__ version of comparisons, as stopping the kernel seems to be inefficient.

Support for GPU through __Openmp__ is planned, and a third row with performances on a __Nvidia gtx1060 6Gb__ will be added.

# Supported operations

## Initializing

### Zero

You can initialize a `Vector` of size `n` filled with zeros by using `Vector(n)`, and a `Matrix` of size `n x m` using `Matrix(n, m)`.

### Diagonal

You can use `mat.diag()` on a square `Matrix` to make it into the identity matrix (ones on the diagonal and zeros elsewhere).

You can also use `mat.diag(vect)` on a suqare `Matrix` of size `n`, with `vect` being a `Vector` of size `n`, to fill the diagonal of `mat` with the elements of `vect`, and make all non-diagonal elements null.

### Randomize

You can use the function `.randomize()` on a `Vector` or a `Matrix` to randomize it using the `rand()` function.

## Reading and writing

You can read and write to a `Vector` or a `Matrix` at a specific index using using the following code :

```cpp
//binary_arithmetic included earlier

int main(int argc, char** argv){
  Matrix mat(2, 2); //initializing
  Vector vect(2); //initializing

  bool b1 = mat(0,1); //read
  bool b2 = vect[0]; //read

  vect[1] = false; //write
  mat(1,0) = true; //write

  vect[0] = mat(1, 1); //read and write
  mat(0, 0) = vect[1]; //read and write
}
```

This uses a intermediary `struct` that passes assignment to `bool` to writing to a specific `bit` of the `Vector` or `Matrix`, and support casting to `bool`.

## Printing

You can "print" a `Vector` or a `Matrix` using the following code :

```cpp
//binary_arithmetic included earlier
#include <iostream>

int main(int argc, char** argv){
  Matrix mat(2, 2); //initializing
  Vector vect(2); //initializing

  std::cout << mat << "\n" << vect; //printing mat, then a new-line, then vect
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

The usual scalar product is supported between `Vectors` or `Matrices` of similar size, and is noted `/`. It returns the number of ones in the bitwise multiplication between the two `Vectors` or `Matrices`.

## Comparisons

### Equality and Inequality

Equality and Inequality, respectively noted `==` and `!=`, is supported between `Vectors` or `Matrices` of similar size.

### Strict and wide inequalities

Strict and wide inequalities are supported between `Vectors` or `Matrices` of similar size, and are implemented by comparing the number of ones in both object. Supported inequalities are the following: `<, >, <=, >=`.

## Self arithmetic

All the previous operations are supported as a "self operator" (the "self operator" supported are the following:  `+=, ^=, -=, &=, *=`)
