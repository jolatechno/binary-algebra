#pragma once

#include <stdint.h>
#include <stdbool.h>

typedef class Utils Utils;

class Utils {
  friend class Vector;
  friend class Matrix;

  private:
    static bool bit_out_of_byte_reversed(uint8_t byte, uint8_t bit);
    static uint8_t byte_out_of_word_reversed(uint64_t word, uint8_t byte);
    static int count_ones_8(uint8_t byte);
    static int count_ones_64(uint64_t word);
};
