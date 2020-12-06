#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "arithmetic.hpp"
#include "self_arithmetic.hpp"
#include "comparaisons.hpp"
#include "initializers.hpp"

#include "../binary_arithmetic/reference_arithmetic/reference_arithmetic.hpp"
#include "../binary_arithmetic/binary_arithmetic.hpp"

int main(int argc, char** argv){
  const reference_arithmetic ref;

  uint16_t i, i_max = 20;
  uint16_t height = 2;
  uint16_t width = 1;

  Matrice mat_square_1(width);
  Matrice mat_square_2(width);

  Matrice mat_nsquare_1(height, width);
  Matrice mat_nsquare_2(height, width);

  Vector vect_1(width);
  Vector vect_2(width);

  Vector vect_3(height);


  /*
  testing initializers
  */


  printf("\ntesting zero initializer with square matrices...\n");
  for (i = 0; i < i_max; i++)
    test_zero_initalizer(ref, width, width);

  printf("testing zero initializer with non-square matrices...\n");
  for (i = 0; i < i_max; i++)
    test_zero_initalizer(ref, height, width);

  printf("testing zero initializer with vectors...\n");
  for (i = 0; i < i_max; i++)
    test_zero_initalizer(ref, width);

  printf("testing random initializer with square matrices...\n");
  test_random(ref, mat_square_1, i_max);

  printf("testing random initializer with non-square matrices...\n");
  test_random(ref, mat_nsquare_1, i_max);

  printf("testing random initializer with Vectors...\n");
  test_random(ref, vect_1, i_max);

  printf("testing diag initializer...\n");
  for (i = 0; i < i_max; i++){
    mat_square_1.randomize(); mat_square_2.randomize();
    test_diag_initializer(ref, mat_square_1, mat_square_2);
  }

  printf("testing diag initializer with a specific diagonal...\n");
  for (i = 0; i < i_max; i++){
    mat_square_1.randomize(); mat_square_2.randomize(); vect_1.randomize();
    test_diag_initializer(ref, mat_square_1, mat_square_2, vect_1);
  }


  /*
  testing comparaisons
  */


  printf("\ntesting comparaisons between square matrices...\n");
  for (i = 0; i < i_max; i++) {
    mat_square_1.randomize(); mat_square_2.randomize();
    test_comp(ref, mat_square_1, mat_square_2); test_comp(ref, mat_square_1, mat_square_1);

    mat_square_1 = Matrice(width);
    test_comp(ref, mat_square_1, false); test_comp(ref, mat_square_1, true);
  }

  printf("testing comparaisons between non-square matrices...\n");
  for (i = 0; i < i_max; i++) {
    mat_nsquare_1.randomize(); mat_nsquare_2.randomize();
    test_comp(ref, mat_nsquare_1, mat_nsquare_2); test_comp(ref, mat_nsquare_1, mat_nsquare_1);

    mat_nsquare_1 = Matrice(height, width);
    test_comp(ref, mat_nsquare_1, false); test_comp(ref, mat_nsquare_1, true);
  }

  printf("testing comparaisons between vectors...\n");
  for (i = 0; i < i_max; i++) {
    vect_1.randomize(); vect_2.randomize();
    test_comp(ref, vect_1, vect_2); test_comp(ref, vect_1, vect_1);

    vect_1 = Vector(width);
    test_comp(ref, vect_1, false); test_comp(ref, vect_1, true);
  }


  /*
  testing transpositions
  */


  printf("\ntesting transpositions of square matrices...\n");
  for (i = 0; i < i_max; i++) {
    mat_square_1.randomize();
    test_transpose(ref, mat_square_1);
  }

  printf("testing transpositions of non-square matrices...\n");
  for (i = 0; i < i_max; i++) {
    mat_nsquare_1.randomize();
    test_transpose(ref, mat_nsquare_1);
  }


  /*
  testing additions
  */


  printf("\ntesting additions between square matrices...\n");
  for (i = 0; i < i_max; i++) {
    mat_square_1.randomize(); mat_square_2.randomize();
    test_addition(ref, mat_square_1, mat_square_2);
  }

  printf("testing additions between non-square matrices...\n");
  for (i = 0; i < i_max; i++) {
    mat_nsquare_1.randomize(); mat_nsquare_2.randomize();
    test_addition(ref, mat_nsquare_1, mat_nsquare_2);
  }

  printf("testing additions between non-square matrices and bits...\n");
  for (i = 0; i < i_max; i++) {
    mat_nsquare_1.randomize();
    test_addition(ref, mat_nsquare_1, true);
    test_addition(ref, mat_nsquare_1, false);
  }

  printf("testing additions between vectors...\n");
  for (i = 0; i < i_max; i++) {
    vect_1.randomize(); vect_2.randomize();
    test_addition(ref, vect_1, vect_2);
  }

  printf("testing additions between vectors ans bits...\n");
  for (i = 0; i < i_max; i++) {
    vect_1.randomize();
    test_addition(ref, vect_1, true);
    test_addition(ref, vect_1, false);
  }


  /*
  testing bitwise multiplications
  */


  printf("\ntesting bitwise multiplication between square matrices...\n");
  for (i = 0; i < i_max; i++) {
    mat_square_1.randomize(); mat_square_2.randomize();
    test_bitwise_multiplication(ref, mat_square_1, mat_square_2);
  }

  printf("testing bitwise multiplication between non-square matrices...\n");
  for (i = 0; i < i_max; i++) {
    mat_nsquare_1.randomize(); mat_nsquare_2.randomize();
    test_bitwise_multiplication(ref, mat_nsquare_1, mat_nsquare_2);
  }

  printf("testing bitwise multiplication between non-square matrices and bits...\n");
  for (i = 0; i < i_max; i++) {
    mat_nsquare_1.randomize();
    test_bitwise_multiplication(ref, mat_nsquare_1, true);
    test_bitwise_multiplication(ref, mat_nsquare_1, false);
  }

  printf("testing bitwise multiplication between vectors...\n");
  for (i = 0; i < i_max; i++) {
    vect_1.randomize(); vect_2.randomize();
    test_bitwise_multiplication(ref, vect_1, vect_2);
  }

  printf("testing bitwise multiplication between vectors ans bits...\n");
  for (i = 0; i < i_max; i++) {
    vect_1.randomize();
    test_bitwise_multiplication(ref, vect_1, true);
    test_bitwise_multiplication(ref, vect_1, false);
  }


  /*
  testing negations
  */


  printf("\ntesting negation of square matrices...\n");
  for (i = 0; i < i_max; i++) {
    mat_square_1.randomize();
    test_negation(ref, mat_square_1);
  }

  printf("testing negation of non-square matrices...\n");
  for (i = 0; i < i_max; i++) {
    mat_nsquare_1.randomize();
    test_negation(ref, mat_nsquare_1);
  }

  printf("testing negation of vectors..\n");
  for (i = 0; i < i_max; i++) {
    vect_1.randomize();
    test_negation(ref, vect_1);
  }


  /*
  testing scalar products
  */


  printf("\ntesting scalar product between square matrices...\n");
  for (i = 0; i < i_max; i++) {
    mat_square_1.randomize(); mat_square_2.randomize();
    test_scalar_product(ref, mat_square_1, mat_square_2);
  }

  printf("testing scalar product between non-square matrices...\n");
  for (i = 0; i < i_max; i++) {
    mat_nsquare_1.randomize(); mat_nsquare_2.randomize();
    test_scalar_product(ref, mat_nsquare_1, mat_nsquare_2);
  }

  printf("testing scalar product between vectors...\n");
  for (i = 0; i < i_max; i++) {
    vect_1.randomize(); vect_2.randomize();
    test_scalar_product(ref, vect_1, vect_2);
  }

  printf("testing integer scalar product between square matrices...\n");
  for (i = 0; i < i_max; i++) {
    mat_square_1.randomize(); mat_square_2.randomize();
    test_integer_scalar_product(ref, mat_square_1, mat_square_2);
  }

  printf("testing integer scalar product between non-square matrices...\n");
  for (i = 0; i < i_max; i++) {
    mat_nsquare_1.randomize(); mat_nsquare_2.randomize();
    test_integer_scalar_product(ref, mat_nsquare_1, mat_nsquare_2);
  }

  printf("testing integer scalar product between vectors...\n");
  for (i = 0; i < i_max; i++) {
    vect_1.randomize(); vect_2.randomize();
    test_integer_scalar_product(ref, vect_1, vect_2);
  }


  /*
  testing multiplications
  */


  printf("\ntesting multiplication between vectors of similar dimensions...\n");
  for (i = 0; i < i_max; i++) {
    vect_1.randomize(); vect_2.randomize();
    test_multiplication(ref, vect_1, vect_2);
  }

  printf("testing multiplication between vectors of different dimensions...\n");
  for (i = 0; i < i_max; i++) {
    vect_1.randomize(); vect_3.randomize();
    test_multiplication(ref, vect_1, vect_3);
  }

  printf("testing multiplication between square matrices and vectors...\n");
  for (i = 0; i < i_max; i++) {
    mat_square_1.randomize(); vect_1.randomize();
    test_multiplication(ref, mat_square_1, vect_1);
  }

  printf("testing multiplication between non-square matrices and vectors...\n");
  for (i = 0; i < i_max; i++) {
    mat_nsquare_1.randomize(); vect_1.randomize();
    test_multiplication(ref, mat_nsquare_1, vect_1);
  }

  printf("testing multiplication between square matrices...\n");
  for (i = 0; i < i_max; i++) {
    mat_square_1.randomize(); mat_square_2.randomize();
    test_multiplication(ref, mat_square_1, mat_square_2);
  }


  /*
  testing self additions
  */


  printf("\ntesting self additions between square matrices...\n");
  for (i = 0; i < i_max; i++) {
    mat_square_1.randomize(); mat_square_2.randomize();
    test_self_addition(ref, mat_square_1, mat_square_2);
  }

  printf("testing self additions between non-square matrices...\n");
  for (i = 0; i < i_max; i++) {
    mat_nsquare_1.randomize(); mat_nsquare_2.randomize();
    test_self_addition(ref, mat_nsquare_1, mat_nsquare_2);
  }

  printf("testing self additions between non-square matrices and bits...\n");
  for (i = 0; i < i_max; i++) {
    mat_nsquare_1.randomize();
    test_self_addition(ref, mat_nsquare_1, true);
    test_self_addition(ref, mat_nsquare_1, false);
  }

  printf("testing self additions between vectors...\n");
  for (i = 0; i < i_max; i++) {
    vect_1.randomize(); vect_2.randomize();
    test_self_addition(ref, vect_1, vect_2);
  }

  printf("testing self additions between vectors ans bits...\n");
  for (i = 0; i < i_max; i++) {
    vect_1.randomize();
    test_self_addition(ref, vect_1, true);
    test_self_addition(ref, vect_1, false);
  }


  /*
  testing self bitwise multiplications
  */


  printf("\ntesting self bitwise multiplication between square matrices...\n");
  for (i = 0; i < i_max; i++) {
    mat_square_1.randomize(); mat_square_2.randomize();
    test_self_bitwise_multiplication(ref, mat_square_1, mat_square_2);
  }

  printf("testing self bitwise multiplication between non-square matrices...\n");
  for (i = 0; i < i_max; i++) {
    mat_nsquare_1.randomize(); mat_nsquare_2.randomize();
    test_self_bitwise_multiplication(ref, mat_nsquare_1, mat_nsquare_2);
  }

  printf("testing self bitwise multiplication between non-square matrices and bits...\n");
  for (i = 0; i < i_max; i++) {
    mat_nsquare_1.randomize();
    test_self_bitwise_multiplication(ref, mat_nsquare_1, true);
    test_self_bitwise_multiplication(ref, mat_nsquare_1, false);
  }

  printf("testing self bitwise multiplication between vectors...\n");
  for (i = 0; i < i_max; i++) {
    vect_1.randomize(); vect_2.randomize();
    test_self_bitwise_multiplication(ref, vect_1, vect_2);
  }

  printf("testing self bitwise multiplication between vectors ans bits...\n");
  for (i = 0; i < i_max; i++) {
    vect_1.randomize();
    test_self_bitwise_multiplication(ref, vect_1, true);
    test_self_bitwise_multiplication(ref, vect_1, false);
  }


  /*
  testing multiplications
  */

  printf("testing self multiplication between square matrices and vectors...\n");
  for (i = 0; i < i_max; i++) {
    mat_square_1.randomize(); vect_1.randomize();
    test_self_multiplication(ref, mat_square_1, vect_1);
  }
  printf("testing self multiplication between square matrices...\n");
  for (i = 0; i < i_max; i++) {
    mat_square_1.randomize(); mat_square_2.randomize();
    test_self_multiplication(ref, mat_square_1, mat_square_2);
  }


  return 0;
}
