/*
read operators
*/


bool Matrice::operator()(uint16_t i, uint16_t j) const {
  assert(i < height * 8);  //check if indices are in range
  assert(j < width * 8);

  uint64_t block = blocks[j/8 + (i/8)*width];
  uint8_t byte = utils->byte_out_of_word_reversed(block, i%8);

  return utils->bit_out_of_byte_reversed(byte, j%8);
}

bool Vector::operator[](uint16_t i) const {
  assert(i < height * 8);  //check if indices are in range

  return utils->bit_out_of_byte_reversed(blocks[i/8], i%8);
}


/*
write operators
*/


void Matrice::write(uint16_t i, uint16_t j, bool bit) {
  assert(i < height * 8);  //check if indices are in range
  assert(j < width * 8);

  uint64_t mask = 1;
  mask <<= 8*(7 - i%8);
  mask <<= 7 - j%8;

  blocks[j/8 + (i/8)*width] &= ~mask;
  if (bit)
    blocks[j/8 + (i/8)*width] |= mask;
}

void Vector::write(uint16_t i, bool bit) {
  assert(i < height * 8);  //check if indices are in range

  uint64_t mask = 1;
  mask <<= 7 - i%8;

  blocks[i/8] &= ~mask;
  if (bit)
    blocks[i/8] |= mask;
}
