//gpu operations
#if defined(_OPENMP) && defined(TARGET)
  void Matrix::to() {
    uint16_t _size = height * width;
    uint64_t *this_blocks = blocks;
    #pragma omp target update to(this_blocks[:_size])
  }

  void Vector::to() {
    uint16_t _height = height;
    uint8_t *this_blocks = blocks;
    #pragma omp target update to(this_blocks[:_height])
  }

  void Matrix::to(int start, int length) {
    uint64_t *this_blocks = blocks;
    #pragma omp target update to(this_blocks[start:length])
  }

  void Vector::to(int start, int length) {
    uint8_t *this_blocks = blocks;
    #pragma omp target update to(this_blocks[start:length])
  }

  void Matrix::from() {
    uint16_t _size = height * width;
    uint64_t *this_blocks = blocks;
    #pragma omp target update from(this_blocks[:_size])
  }

  void Vector::from() {
    uint16_t _height = height;
    uint8_t *this_blocks = blocks;
    #pragma omp target update from(this_blocks[:_height])
  }

  void Matrix::from(int start, int length) {
    uint64_t *this_blocks = blocks;
    #pragma omp target update from(this_blocks[start:length])
  }

  void Vector::from(int start, int length) {
    uint8_t *this_blocks = blocks;
    #pragma omp target update from(this_blocks[start:length])
  }
#endif
