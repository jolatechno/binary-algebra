#include <stdint.h>
#include <stdbool.h>
#include <omp.h>

/*
block transposition
*/


inline uint64_t Matrix::transpose_block(uint64_t const& block) const {
  // stolen from the Hacker's delight, edition 2, chapter 7 part 3
  uint64_t res = block & 0xAA55AA55AA55AA55LL |
  (block & 0x00AA00AA00AA00AALL) << 7 |
  (block >> 7) & 0x00AA00AA00AA00AALL;
  res = res & 0xCCCC3333CCCC3333LL |
  (res & 0x0000CCCC0000CCCCLL) << 14 |
  (res >> 14) & 0x0000CCCC0000CCCCLL;
  res = res & 0xF0F0F0F00F0F0F0FLL |
  (res & 0x00000000F0F0F0F0LL) << 28 |
  (res >> 28) & 0x00000000F0F0F0F0LL;

  return res;
}


/*
block multiplications
*/


inline  uint8_t Matrix::multiply_block_byte(uint64_t const& block, uint8_t const& vect) const { //changed to acomodate the switch in block indices, check the readme
  uint8_t sum = 0x00;

  //uint64_t block_t = transpose_block(block);

  for (int8_t i = 0; i < 8; i++)
    sum ^= utils->byte_out_of_word_reversed(block, i) * utils->bit_out_of_byte_reversed(vect, i); //utils->byte_out_of_word_reversed(block_t, i) * utils->bit_out_of_byte_reversed(vect, i);

  return sum;
}

inline  uint64_t Matrix::multiply_block_block(uint64_t const& block_left, uint64_t const& block_right) const { //changed to acomodate the switch in block indices, check the readme
  uint64_t res = 0;
  //uint64_t block_right_t = transpose_block(block_right);

  for (int8_t i = 0; i < 8; i++)
    res = (res << 8) | multiply_block_byte(block_left, utils->byte_out_of_word_reversed(block_right, i)); //multiply_block_byte(block_right_t, utils->byte_out_of_word_reversed(block_left, i));

  return res;
}


inline  uint64_t Vector::multiply_byte_byte(uint8_t const& vect_left, uint8_t const& vect_right) const { //changed to acomodate the switch in block indices, check the readme
  uint64_t res = 0;

  for (int8_t i = 0; i < 8; i++)
    res = (res << 8) | (vect_right * utils->bit_out_of_byte_reversed(vect_left, i)); //(vect_left * utils->bit_out_of_byte_reversed(vect_right, i));

  return res;
}

#if defined(_OPENMP) && defined(TARGET)
  inline uint64_t Matrix::multiply_block_word(uint64_t const& block0, uint64_t const& block1, uint64_t const& block2, uint64_t const& block3, \
    uint64_t const& block4, uint64_t const& block5, uint64_t const& block6, uint64_t const& block7, \
    uint8_t const& vect) const {
    uint64_t res = multiply_block_byte(block7, vect);
    res = (res << 8) | multiply_block_byte(block6, vect);
    res = (res << 8) | multiply_block_byte(block5, vect);
    res = (res << 8) | multiply_block_byte(block4, vect);
    res = (res << 8) | multiply_block_byte(block3, vect);
    res = (res << 8) | multiply_block_byte(block2, vect);
    res = (res << 8) | multiply_block_byte(block1, vect);

    return (res << 8) | multiply_block_byte(block0, vect);
  }
#endif
