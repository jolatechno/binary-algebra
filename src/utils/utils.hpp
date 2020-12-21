#pragma once

#include <stdint.h>
#include <stdbool.h>

typedef class Utils Utils;

class Utils {
  friend class Vector;
  friend class Matrix;

  private:
    #if defined(_OPENMP) &&  defined(TARGET)
      #pragma omp declare target
    #endif
    inline bool bit_out_of_byte_reversed(uint8_t byte, uint8_t bit);
    inline uint8_t byte_out_of_word_reversed(uint64_t word, uint8_t byte);
    inline int count_ones_8(uint8_t byte);
    inline int count_ones_64(uint64_t word);

    inline void _atomic_xor_fetch_8(uint8_t &x1, uint8_t x2); //because openmp dosen't implement it on GPUs
    inline void _atomic_xor_fetch_64(uint64_t &x1, uint64_t x2);
    #if defined(_OPENMP) &&  defined(TARGET)
      #pragma omp end declare target
    #endif
};

inline bool Utils::bit_out_of_byte_reversed(uint8_t byte, uint8_t bit) {
  return (byte >> (7 - bit)) & 0x01;
}

inline uint8_t Utils::byte_out_of_word_reversed(uint64_t word, uint8_t byte) {
  return word >> 8*(7 - byte);
}

inline int Utils::count_ones_8(uint8_t byte) {
  const int NIBBLE_LOOKUP [16] = {
    0, 1, 1, 2, 1, 2, 2, 3,
    1, 2, 2, 3, 2, 3, 3, 4
  };

  return NIBBLE_LOOKUP[byte & 0x0F] + NIBBLE_LOOKUP[byte >> 4];
}

inline int Utils::count_ones_64(uint64_t word) {
  int sum = 0;

  for (uint8_t i = 0; i < 8; i++)
    sum += count_ones_8(byte_out_of_word_reversed(word, i));

  return sum;
}

inline void Utils::_atomic_xor_fetch_8(uint8_t &x1, uint8_t x2) {
  #if defined(_OPENMP)
    #if defined(TARGET)
      #pragma omp critical
      x1 ^= x2;
    #else
      #pragma omp atomic
      x1 ^= x2;
    #endif
  #else
    x1 ^= x2;
  #endif
}

inline void Utils::_atomic_xor_fetch_64(uint64_t &x1, uint64_t x2) {
  #if defined(_OPENMP)
    #if defined(TARGET)
      #pragma omp critical
      x1 ^= x2;
    #else
      #pragma omp atomic
      x1 ^= x2;
    #endif
  #else
    x1 ^= x2;
  #endif
}
