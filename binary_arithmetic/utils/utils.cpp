#include <stdint.h>
#include <stdbool.h>

#include "utils.hpp"

uint8_t Utils::bit_out_of_byte_reversed(uint8_t byte, uint8_t bit) {
  return (byte >> (7 - bit)) & 0x01;
}

uint8_t Utils::byte_out_of_word_reversed(uint64_t word, uint8_t byte) {
  return word >> 8*(7 - byte);
}

uint8_t Utils::circular_shift_8(uint8_t vect, uint8_t shift) {
  return (vect << shift) | (vect >> 8 - shift);
}

uint64_t Utils::circular_shift_64(uint64_t vect, uint8_t shift) {
  return (vect << shift) | (vect >> 64 - shift);
}
