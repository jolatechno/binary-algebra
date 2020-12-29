//gpu operations
#if defined(_OPENMP) && defined(TARGET)
  void Matrix::to() {
    uint16_t _size = height * width;
    auto *this_blocks = blocks;
    #pragma omp target update to(this_blocks[:_size])
  }

  void Vector::to() {
    uint16_t _height = height;
    auto *this_blocks = blocks;
    #pragma omp target update to(this_blocks[:_height])
  }

  void Matrix::to(int start, int end) {
    auto *this_blocks = &blocks[start];
    #pragma omp target update to(this_blocks[:end - start])
  }

  void Vector::to(int start, int end) {
    auto *this_blocks = &blocks[start];
    #pragma omp target update to(this_blocks[:end - start])
  }

  void Matrix::from() {
    uint16_t _size = height * width;
    auto *this_blocks = blocks;
    #pragma omp target update from(this_blocks[:_size])
  }

  void Vector::from() {
    uint16_t _height = height;
    auto *this_blocks = blocks;
    #pragma omp target update to(this_blocks[:_height])
  }

  void Matrix::from(int start, int end) {
    auto *this_blocks = &blocks[start];
    #pragma omp target update from(this_blocks[:end - start])
  }

  void Vector::from(int start, int end) {
    auto *this_blocks = &blocks[start];
    #pragma omp target update from(this_blocks[:end - start])
  }
#endif
