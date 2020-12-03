/*
randomizers
*/


void Matrice::randomize() {
  uint8_t *block_8 = (uint8_t *)&blocks[0];

  #pragma omp parallel for
  for (int16_t i = 0; i < height * width * 8; i++)
    block_8[i] = rand();
}

void Vector::randomize() {
  #pragma omp parallel for
  for (int16_t i = 0; i < height; i++)
    blocks[i] = rand();
}


/*
assignment operators
*/


Matrice& Matrice::operator=(const Matrice other) {
  if(this != &other) {
    assert(height == other.height); //check if dimensions are compatible
    assert(width == other.width);

    memcpy(blocks, other.blocks, height * width * sizeof(uint64_t)); //copy blocks
  }
  return *this;
}

Vector& Vector::operator=(const Vector other) {
  if(this != &other) {
    assert(height == other.height); //check if dimensions are compatible

    memcpy(blocks, other.blocks, height * sizeof(uint8_t)); //copy blocks
  }
  return *this;
}


/*
diagonal initializers
*/


void Matrice::diag() {
  assert(height == width);//check if dimensions are compatible

  #pragma omp parallel for collapse(2)
  for (int16_t i = 0; i < height; i++)
    for (int16_t j = 0; j < width; j++)
      if(i == j) {
        blocks[i + j*height] = 0x8040201008040201;
      } else {
        blocks[i + j*height] = 0;
      }
}

void Matrice::diag(const Vector diagonal) {
  assert(height == width); //check if dimensions are compatible
  assert(diagonal.height == height);

  #pragma omp parallel for collapse(2)
  for (int16_t i = 0; i < height; i++)
    for (int16_t j = 0; j < width; j++)
      if(i == j) {
        uint8_t block = diagonal.blocks[i];
        uint64_t res = 0;

        for (int16_t k = 7; k >= 0; k--)
          res = (res << 9) | ((block >> k) & 0x01);

          blocks[i + j*height] = res;
      } else {
        blocks[i + j*height] = 0;
      }
}
