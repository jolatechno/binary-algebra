#include <stdint.h>
#include <stdio.h>

#include "../binary_arithmetic/binary_arithmetic.hpp"

#include "utils.hpp"
#include "functions.hpp"

int main(int argc, char** argv){
  const int n_iter = 50;
  #if defined(_OPENMP)
    const int sizes[] = {
      10, 100, 1000,
    };
  #else
    const int sizes[] = {
      10, 50, 100,
    };
  #endif

  const int n_sizes = sizeof(sizes)/sizeof(sizes[0]);

  /*
  transposition
  */


  printf("\n");
  timeit(transposition, "Matrix transposition: %f %s for size=%dbit\n", n_iter, sizes, n_sizes);


  /*
  equality
  */


  printf("\n\n");
  timeit(equal_mat, "Matrix equality: %f %s for size=%dbit\n", n_iter, sizes, n_sizes);

  printf("\n");
  timeit(equal_vect, "Vector equality: %f %s for size=%dbit\n", n_iter, sizes, n_sizes);


  /*
  comparaison
  */


  printf("\n\n");
  timeit(comparaisons_mat, "Matrix comparison: %f %s for size=%dbit\n", n_iter, sizes, n_sizes);

  printf("\n");
  timeit(comparaisons_vect, "Vector comparison: %f %s for size=%dbit\n", n_iter, sizes, n_sizes);


  /*
  addition
  */


  printf("\n\n");
  timeit(additions_mat, "Matrix addition: %f %s for size=%dbit\n", n_iter, sizes, n_sizes);

  printf("\n");
  timeit(additions_vect, "Vector addition: %f %s for size=%dbit\n", n_iter, sizes, n_sizes);


  /*
  scalar products
  */


  printf("\n\n");
  timeit(scalar_product_mat, "Matrix scalar product: %f %s for size=%dbit\n", n_iter, sizes, n_sizes);

  printf("\n");
  timeit(scalar_product_vect, "Vector scalar product: %f %s for size=%dbit\n", n_iter, sizes, n_sizes);

  printf("\n");
  timeit(integer_scalar_product_mat, "Matrix integer scalar product: %f %s for size=%dbit\n", n_iter, sizes, n_sizes);

  printf("\n");
  timeit(integer_scalar_product_vect, "Vector integer scalar product: %f %s for size=%dbit\n", n_iter, sizes, n_sizes);


  /*
  multiplciations
  */


  printf("\n\n");
  timeit(multiplication_vect, "Vector multiplication with vector: %f %s for size=%dbit\n", n_iter, sizes, n_sizes);

  printf("\n");
  timeit(multiplication_mat_vect, "Matrix multiplication with vector: %f %s for size=%dbit\n", n_iter, sizes, n_sizes);

  printf("\n");
  timeit(multiplication_mat, "Matrix multiplication with Matrix  %f %s for size=%dbit\n", n_iter, sizes, n_sizes);

}
