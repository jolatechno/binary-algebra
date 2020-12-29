bool_from_byte::operator bool() const {
  return utils->bit_out_of_byte_reversed(*byte, i);
}

bool_from_word::operator bool() const {
  uint8_t byte = utils->byte_out_of_word_reversed(*word, j); //i%8);
  return utils->bit_out_of_byte_reversed(byte, i); //j%8);
}

bool_from_byte& bool_from_byte::operator=(bool value) {
  uint8_t mask = 1;
  mask <<= 7 - i;

  *byte &= ~mask;
  if (value)
    *byte |= mask;

  #if defined(_OPENMP) && defined(TARGET)
    auto *_byte = byte;
    #pragma omp target update to(_byte)
  #endif

  return *this;
}

bool_from_word& bool_from_word::operator=(bool value) {
  uint64_t mask = 1;
  mask <<= 8*(7 - j);;
  mask <<= 7 - i;;

  *word &= ~mask;
  if (value)
    *word |= mask;

  #if defined(_OPENMP) && defined(TARGET)
    auto *_word = word;
    #pragma omp target update to(_word)
  #endif

  return *this;
}


/*
read operators
*/


bool_from_word Matrix::operator()(uint16_t i, uint16_t j) const { //changed to acomodate the switch in block indices, check the readme
  assert(i < height * 8);  //check if indices are in range
  assert(j < width * 8);

  uint64_t *block = &blocks[j/8 + (i/8)*width];
  return bool_from_word(i%8, j%8, block);
}

bool_from_byte Vector::operator[](uint16_t i) const {
  assert(i < height * 8);  //check if indices are in range

  return bool_from_byte(i%8, &blocks[i/8]);
}
