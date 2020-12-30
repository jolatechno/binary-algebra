//gpu operations
#if defined(_OPENMP) && defined(TARGET)
  void Matrix::to() {
    int _size = height * width;
    uint64_t *this_blocks = blocks;
    #pragma omp target update to(this_blocks[:_size])
  }

  void Vector::to() {
    int _height = height;
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
    int _size = height * width;
    uint64_t *this_blocks = blocks;
    #pragma omp target update from(this_blocks[:_size])
  }

  void Vector::from() {
    int _height = height;
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
