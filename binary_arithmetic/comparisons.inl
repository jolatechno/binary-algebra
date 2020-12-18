#define COMPARAISON_VARIABLE_HEADER \
  auto *other_blocks = other.blocks; \
  auto *this_blocks = blocks;

#define COMPARAISON_MATRIX_BITWISE_HEADER \
  assert(height == other.height); \
  assert(width == other.width); \
  auto _width = width; \
  auto _height = height;

#define COMPARAISON_VECTOR_BITWISE_HEADER \
  assert(height == other.height); \
  auto _height = height;


/*
equality between objects
*/


bool Matrix::operator==(Matrix const& other) const {
  if (this != &other) {
    COMPARAISON_MATRIX_BITWISE_HEADER;
    COMPARAISON_VARIABLE_HEADER;

    bool equal_ = true;

    int16_t n;
    #if defined(_OPENMP)
      #pragma omp parralel shared(this_blocks, other_blocks, _equal)
      #pragma omp for
    #endif
    for (n = 0; n < _height * _width; n++) {
      if (this_blocks[n] != other_blocks[n]) {
        #if defined(_OPENMP)
          #pragma omp critical
          equal_ = false;
          #pragma omp cancel for
        #else
          return false;
        #endif

      }
      #if defined(_OPENMP)
        #pragma omp cancellation point for
      #endif
    }

    return equal_;
  }

  return true;
}

bool Vector::operator==(Vector const& other) const {
  if (this != &other) {
    COMPARAISON_VECTOR_BITWISE_HEADER;
    COMPARAISON_VARIABLE_HEADER;

    bool equal_ = true;

    int16_t i;
    #if defined(_OPENMP)
      #pragma omp parralel shared(this_blocks, other_blocks, _equal)
      #pragma omp for
    #endif
    for (i = 0; i < _height; i++) {
      if (this_blocks[i] != other_blocks[i]) {
        #if defined(_OPENMP)
          #pragma omp critical
          equal_ = false;
          #pragma omp cancel for
        #else
          return false;
        #endif

      }
      #if defined(_OPENMP)
        #pragma omp cancellation point for
      #endif
    }

    return equal_;
  }

  return true;
}


/*
equality with bits
*/


bool Matrix::operator==(const bool bit) const {
  bool equal_ = true;
  uint64_t target = bit ? 0xFFFFFFFFFFFFFFFF : 0;

  auto *this_blocks = blocks;
  auto _size = height * width;

  int16_t n;
  #if defined(_OPENMP)
    #pragma omp parralel shared(this_blocks, other_blocks, _equal)
    #pragma omp for
  #endif
  for (n = 0; n < _size; n++) {
    if (this_blocks[n] != target) {
      #if defined(_OPENMP)
        #pragma omp critical
        equal_ = false;
        #pragma omp cancel for
      #else
        return false;
      #endif

    }
    #if defined(_OPENMP)
      #pragma omp cancellation point for
    #endif
  }

  return equal_;
}

bool Vector::operator==(const bool bit) const {
  bool equal_ = true;
  uint8_t target = bit ? 0xFF : 0;

  auto *this_blocks = blocks;
  auto _height = height;

  int16_t i;
  #if defined(_OPENMP)
    #pragma omp parralel shared(this_blocks, other_blocks, _equal)
    #pragma omp for
  #endif
  for (i = 0; i < _height; i++) {
    if (this_blocks[i] != target) {
      #if defined(_OPENMP)
        #pragma omp critical
        equal_ = false;
        #pragma omp cancel for
      #else
        return false;
      #endif

    }
    #if defined(_OPENMP)
      #pragma omp cancellation point for
    #endif
  }

  return equal_;
}


/*
smaller than comparaisons
*/


int Matrix::difference(Matrix const& other) const {
  if (this != &other) {
    COMPARAISON_MATRIX_BITWISE_HEADER;
    COMPARAISON_VARIABLE_HEADER;

    int diff = 0;

    int16_t n;
    #if defined(_OPENMP)
      #pragma omp parallel for reduction(+ : diff) shared(this_blocks, other_blocks)
    #endif
    for (n = 0; n < _height * _width; n++)
      diff +=  utils->count_ones_64(this_blocks[n]) - utils->count_ones_64(other_blocks[n]);

    return diff;
  }

  return 0;
}

int Vector::difference(Vector const& other) const {
  if (this != &other) {
    COMPARAISON_VECTOR_BITWISE_HEADER;
    COMPARAISON_VARIABLE_HEADER;

    int diff = 0;

    int16_t i;
    #if defined(_OPENMP)
      #pragma omp parallel for reduction(+ : diff) shared(this_blocks, other_blocks)
    #endif
    for (i = 0; i < height; i++)
      diff +=  utils->count_ones_8(this_blocks[i]) - utils->count_ones_8(other_blocks[i]);

    return diff;
  }

  return 0;
}


/*
other comparaison obtained from all the above
*/


bool Matrix::operator!=(Matrix const& other) const {
  return !(*this == other);
}

bool Vector::operator!=(Vector const& other) const {
  return !(*this == other);
}

bool Matrix::operator!=(const bool bit) const {
  return !(*this == bit);
}

bool Vector::operator!=(const bool bit) const {
  return !(*this == bit);
}

bool Matrix::operator<(Matrix const& other) const {
  return this->difference(other) < 0;
}

bool Vector::operator<(Vector const& other) const {
  return this->difference(other) < 0;
}

bool Matrix::operator<(const bool bit) const {
  if (bit)
    return !(*this == true);
  return true;
}

bool Vector::operator<(const bool bit) const {
  if (bit)
    return !(*this == true);
  return true;
}

bool Matrix::operator>(Matrix const& other) const {
  return this->difference(other) > 0;
}

bool Vector::operator>(Vector const& other) const {
  return this->difference(other) > 0;
}

bool Matrix::operator>(const bool bit) const {
  if (bit)
    return false;
  return !(*this == false);
}

bool Vector::operator>(const bool bit) const {
  if (bit)
    return false;
  return !(*this == false);
}

bool Matrix::operator<=(Matrix const& other) const {
  return this->difference(other) <= 0;
}

bool Vector::operator<=(Vector const& other) const {
  return this->difference(other) <= 0;
}

bool Matrix::operator<=(const bool bit) const {
  return bit;
}

bool Vector::operator<=(const bool bit) const {
  return bit;
}

bool Matrix::operator>=(Matrix const& other) const {
  return this->difference(other) >= 0;
}

bool Vector::operator>=(Vector const& other) const {
  return this->difference(other) >= 0;
}


bool Matrix::operator>=(const bool bit) const {
  if (bit)
    return *this == true;
  return true;
}

bool Vector::operator>=(const bool bit) const {
  if (bit)
    return *this == true;
  return true;
}
