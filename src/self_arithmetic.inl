/*
additions
*/


void Matrix::operator^=(Matrix const& other) {
  COMPARAISON_MATRIX_BITWISE_HEADER;
  COMPARAISON_VARIABLE_HEADER;

  int16_t n;
  #if defined(_OPENMP) && defined(TARGET)
    if(_size > GPU_LIMIT) {
      #pragma omp target teams distribute parallel for map(tofrom:this_blocks[:_size]) map(to:other_blocks[:_size])
      for (n = 0; n < _size; n++)
        this_blocks[n] ^= other_blocks[n];
    } else {
  #endif

  _OPENMP_PRAGMA("omp parallel for schedule(static) if(_size > CPU_LIMIT)")
  for (n = 0; n < _size; n++)
    this_blocks[n] ^= other_blocks[n];

  #if defined(_OPENMP) && defined(TARGET)
    }
  #endif
}

void Matrix::operator+=(Matrix const& other) {
  *this ^= other;
}

void Matrix::operator-=(Matrix const& other) {
  *this ^= other;
}

void Matrix::operator^=(const bool bit) {
  if (bit) {
    uint64_t *this_blocks = blocks;

    uint16_t _size = height * width;

    int16_t n;
    #if defined(_OPENMP) && defined(TARGET)
      if(_size > GPU_LIMIT) {
        #pragma omp target teams distribute parallel for map(tofrom:this_blocks[:_size])
        for (n = 0; n < _size; n++)
          this_blocks[n] = ~this_blocks[n];
      } else {
    #endif

    _OPENMP_PRAGMA("omp parallel for schedule(static) if(_size > CPU_LIMIT)")
    for (n = 0; n < _size; n++)
      this_blocks[n] = ~this_blocks[n];

    #if defined(_OPENMP) && defined(TARGET)
      }
    #endif
  }
}

void Matrix::operator+=(const bool bit) {
  *this ^= bit;
}

void Matrix::operator-=(const bool bit) {
  *this ^= bit;
}

void Vector::operator^=(Vector const& other) {
  COMPARAISON_VECTOR_BITWISE_HEADER;
  COMPARAISON_VARIABLE_HEADER;

  int16_t i;
  #if defined(_OPENMP) && defined(TARGET)
    if(_height > GPU_LIMIT) {
      #pragma omp target teams distribute parallel for map(tofrom:this_blocks[:_height]) map(to:other_blocks[:_height])
      for (i = 0; i < _height; i++)
        this_blocks[i] ^= other_blocks[i];
    } else {
  #endif

  _OPENMP_PRAGMA("omp parallel for schedule(static) if(_height > CPU_LIMIT)")
  for (i = 0; i < _height; i++)
    this_blocks[i] ^= other_blocks[i];

  #if defined(_OPENMP) && defined(TARGET)
    }
  #endif
}

void Vector::operator+=(Vector const& other) {
  *this ^= other;
}

void Vector::operator-=(Vector const& other) {
  *this ^= other;
}

void Vector::operator^=(const bool bit) {
  if (bit) {
    uint8_t *this_blocks = blocks;

    uint16_t _height = height;

    int16_t i;
    #if defined(_OPENMP) && defined(TARGET)
      if(_height > GPU_LIMIT) {
        #pragma omp target teams distribute parallel for map(tofrom:this_blocks[:_height])
        for (i = 0; i < _height; i++)
          this_blocks[i] = ~this_blocks[i];
      } else {
    #endif

    _OPENMP_PRAGMA("omp parallel for schedule(static) if(_height > CPU_LIMIT)")
    for (i = 0; i < _height; i++)
      this_blocks[i] = ~this_blocks[i];

    #if defined(_OPENMP) && defined(TARGET)
      }
    #endif
  }
}

void Vector::operator+=(const bool bit) {
  *this ^= bit;
}

void Vector::operator-=(const bool bit) {
  *this ^= bit;
}


/*
bitwise multiplications
*/


void Matrix::operator&=(Matrix const& other) {
  COMPARAISON_MATRIX_BITWISE_HEADER;
  COMPARAISON_VARIABLE_HEADER;

  int16_t n;
  #if defined(_OPENMP) && defined(TARGET)
    if(_size > GPU_LIMIT) {
      #pragma omp target teams distribute parallel for map(tofrom:this_blocks[:_size]) map(to:other_blocks[:_size])
      for (n = 0; n < _size; n++)
        this_blocks[n] &= other_blocks[n];
    } else {
  #endif

  _OPENMP_PRAGMA("omp parallel for schedule(static) if(_size > CPU_LIMIT)")
  for (n = 0; n < _size; n++)
    this_blocks[n] &= other_blocks[n];

  #if defined(_OPENMP) && defined(TARGET)
    }
  #endif
}

void Matrix::operator&=(const bool bit) {
  if (!bit)
    memset(blocks, 0, height * width * sizeof(uint64_t));
}

void Vector::operator&=(Vector const& other) {
  COMPARAISON_VECTOR_BITWISE_HEADER;
  COMPARAISON_VARIABLE_HEADER;

  int16_t i;
  #if defined(_OPENMP) && defined(TARGET)
    if(_height > GPU_LIMIT) {
      #pragma omp target teams distribute parallel for map(tofrom:this_blocks[:_height]) map(to:other_blocks[:_height])
      for (i = 0; i < _height; i++)
        this_blocks[i] &= other_blocks[i];
    } else {
  #endif

  _OPENMP_PRAGMA("omp parallel for schedule(static) if(_height > CPU_LIMIT)")
  for (i = 0; i < _height; i++)
    this_blocks[i] &= other_blocks[i];

  #if defined(_OPENMP) && defined(TARGET)
    }
  #endif
}

void Vector::operator&=(const bool bit) {
  if (!bit)
    memset(blocks, 0, height * sizeof(uint8_t));
}


/*
multiplications
*/


void Matrix::operator*=(Matrix const& other) {
  assert(height == width); //check if dimensions are compatible
  assert(other.height == other.width);

  *this = (*this) * other;
}

void Vector::operator*=(Matrix const& other) {
  assert(other.height == other.width); //check if dimensions are compatible

  *this =  other * (*this);
}
