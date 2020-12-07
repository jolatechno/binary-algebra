#include <stdint.h>
#include <stdbool.h>
#include <omp.h>

/*
block transposition
*/


uint64_t Matrice::transpose_block(uint64_t block) const {
  // stolen from the Hacker's delight, edition 2, chapter 7 part 3
  block = block & 0xAA55AA55AA55AA55LL |
  (block & 0x00AA00AA00AA00AALL) << 7 |
  (block >> 7) & 0x00AA00AA00AA00AALL;
  block = block & 0xCCCC3333CCCC3333LL |
  (block & 0x0000CCCC0000CCCCLL) << 14 |
  (block >> 14) & 0x0000CCCC0000CCCCLL;
  block = block& 0xF0F0F0F00F0F0F0FLL |
  (block & 0x00000000F0F0F0F0LL) << 28 |
  (block >> 28) & 0x00000000F0F0F0F0LL;

  return block;
}


/*
block multiplications
*/


uint8_t Matrice::multiply_block_byte(uint64_t block, uint8_t vect) const { //changed to acomodate the switch in block indices, check the readme
  uint8_t sum = 0x00;
  //uint64_t block_t = transpose_block(block);

  for (int8_t i = 0; i < 8; i++)
    sum ^= utils->byte_out_of_word_reversed(block, i) * utils->bit_out_of_byte_reversed(vect, i); //utils->byte_out_of_word_reversed(block_t, i) * utils->bit_out_of_byte_reversed(vect, i);

  return sum;
}

uint64_t Matrice::multiply_block_block(uint64_t block_left, uint64_t block_right) const { //changed to acomodate the switch in block indices, check the readme
  uint64_t res = 0;
  //uint64_t block_right_t = transpose_block(block_right);

  for (int8_t i = 0; i < 8; i++)
    res = (res << 8) | multiply_block_byte(block_left, utils->byte_out_of_word_reversed(block_right, i)); //multiply_block_byte(block_right_t, utils->byte_out_of_word_reversed(block_left, i));

  return res;
}

uint64_t Vector::multiply_byte_byte(uint8_t vect_left, uint8_t vect_right) const { //changed to acomodate the switch in block indices, check the readme
  uint64_t res = 0;

  for (int8_t i = 0; i < 8; i++)
    res = (res << 8) | (vect_right * utils->bit_out_of_byte_reversed(vect_left, i)); //(vect_left * utils->bit_out_of_byte_reversed(vect_right, i));

  return res;
}
