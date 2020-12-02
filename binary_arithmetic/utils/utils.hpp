#pragma once

#include <stdint.h>
#include <stdbool.h>

typedef class Utils Utils;

class Utils {
  friend class Vector;
  friend class Matrice;

  private:
    uint8_t bit_out_of_byte_reversed(uint8_t byte, uint8_t bit);
    uint8_t byte_out_of_word_reversed(uint64_t word, uint8_t byte);
    uint8_t circular_shift_8(uint8_t vect, uint8_t shift);
    uint64_t circular_shift_64(uint64_t vect, uint8_t shift);
};
