#pragma once

#include <stdint.h>
#include <stdbool.h>

#include "../openmp.hpp"

typedef class Utils Utils;

class Utils {
  public:
    _OPENMP_GPU_PRAGMA("omp declare target")
    static inline bool bit_out_of_byte_reversed(uint8_t const& byte, uint8_t const& bit);
    static inline uint8_t byte_out_of_word_reversed(uint64_t const& word, uint8_t const& byte);
    static inline int count_ones_8(uint8_t const& byte);
    static inline int count_ones_64(uint64_t const& word);
    _OPENMP_GPU_PRAGMA("omp end declare target")
};

inline bool Utils::bit_out_of_byte_reversed(uint8_t const& byte, uint8_t const& bit) {
  return (byte >> (7 - bit)) & 0x01;
}

inline uint8_t Utils::byte_out_of_word_reversed(uint64_t const& word, uint8_t const& byte) {
  return word >> 8*(7 - byte);
}

inline int Utils::count_ones_8(uint8_t const& byte) {
  const int NIBBLE_LOOKUP [16] = {
    0, 1, 1, 2, 1, 2, 2, 3,
    1, 2, 2, 3, 2, 3, 3, 4
  };

  return NIBBLE_LOOKUP[byte & 0x0F] + NIBBLE_LOOKUP[byte >> 4];
}

inline int Utils::count_ones_64(uint64_t const& word) {
  int sum = 0;

  for (uint8_t i = 0; i < 8; i++)
    sum += count_ones_8(byte_out_of_word_reversed(word, i));

  return sum;
}
