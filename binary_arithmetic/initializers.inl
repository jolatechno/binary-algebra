#define INITIALIZER_SQUARE_Matrix_HEADER \
  assert(height == width); \
  auto *this_blocks = blocks; \
  auto _height = height; \
  auto _width = width;

#define INITIALIZER_VECTOR_HEADER \
  auto *this_blocks = blocks; \
  auto _height = height;


/*
randomizers
*/


void Matrix::randomize() {
  uint8_t *block_8 = (uint8_t *)blocks;

  uint16_t _size = height * width * 8;

  int16_t i;
  #pragma omp parallel for shared(block_8)
  for (i = 0; i < _size; i++)
    block_8[i] = rand();
}

void Vector::randomize() {
  INITIALIZER_VECTOR_HEADER;

  int16_t i;
  #pragma omp parallel for shared(this_blocks)
  for (i = 0; i < _height; i++)
    this_blocks[i] = rand();
}

/*
assignment operators
*/


Matrix& Matrix::operator=(Matrix const& other) {
  if(this != &other) {
    assert(height == other.height); //check if dimensions are compatible
    assert(width == other.width);

    memcpy(blocks, other.blocks, height * width * sizeof(uint64_t)); //copy blocks
  }
  return *this;
}

Vector& Vector::operator=(Vector const& other) {
  if(this != &other) {
    assert(height == other.height); //check if dimensions are compatible

    memcpy(blocks, other.blocks, height * sizeof(uint8_t)); //copy blocks
  }
  return *this;
}


/*
diagonal initializers
*/


void Matrix::diag() {
  INITIALIZER_SQUARE_Matrix_HEADER;

  int16_t i, j;
  #pragma omp parallel for collapse(2) shared(this_blocks)
  for (i = 0; i < _height; i++)
    for (j = 0; j < _width; j++)
      if(i == j) {
        this_blocks[i + j*_height] = 0x8040201008040201;
      } else {
        this_blocks[i + j*_height] = 0;
      }
}

void Matrix::diag(Vector const& diagonal) {
  INITIALIZER_SQUARE_Matrix_HEADER;

  int16_t i, j;
  #pragma omp parallel for collapse(2) shared(this_blocks)
  for (i = 0; i < _height; i++)
    for (j = 0; j < _width; j++)
      if(i == j) {
        uint8_t block = diagonal.blocks[i];
        uint64_t res = 0;

        for (int16_t k = 7; k >= 0; k--)
          res = (res << 9) | ((block >> k) & 0x01);

          blocks[i + j*_height] = res;
      } else {
        blocks[i + j*_height] = 0;
      }
}
