/*
additions
*/


void Matrice::operator^=(Matrice const& other) {
  COMPARAISON_MATRICE_BITWISE_HEADER;
  COMPARAISON_VARIABLE_HEADER;

  int16_t n;
  #pragma omp parallel for schedule(static) shared(this_blocks, other_blocks)
  for (n = 0; n < _height * _width; n++)
    this_blocks[n] ^= other_blocks[n];
}

void Matrice::operator+=(Matrice const& other) {
  *this ^= other;
}

void Matrice::operator-=(Matrice const& other) {
  *this ^= other;
}

void Matrice::operator^=(const bool bit) {
  if (bit) {
    uint64_t *this_blocks = blocks;

    uint16_t _size = height * width;

    int16_t n;
    #pragma omp parallel for schedule(static) shared(this_blocks)
    for (n = 0; n < _size; n++)
      this_blocks[n] = ~this_blocks[n];
  }
}

void Matrice::operator+=(const bool bit) {
  *this ^= bit;
}

void Matrice::operator-=(const bool bit) {
  *this ^= bit;
}

void Vector::operator^=(Vector const& other) {
  COMPARAISON_VECTOR_BITWISE_HEADER;
  COMPARAISON_VARIABLE_HEADER;

  int16_t i;
  #pragma omp parallel for schedule(static) shared(this_blocks, other_blocks)
  for (i = 0; i < height; i++)
    this_blocks[i] ^= other_blocks[i];
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
    #pragma omp parallel for schedule(static) shared(this_blocks)
    for (i = 0; i < _height; i++)
      this_blocks[i] = ~this_blocks[i];
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


void Matrice::operator&=(Matrice const& other) {
  COMPARAISON_MATRICE_BITWISE_HEADER;
  COMPARAISON_VARIABLE_HEADER;

  int16_t n;
  #pragma omp parallel for schedule(static) shared(this_blocks, other_blocks)
  for (n = 0; n < _height * _width; n++)
    this_blocks[n] &= other_blocks[n];
}

void Matrice::operator&=(const bool bit) {
  if (!bit)
    memset(blocks, 0, height * width * sizeof(uint64_t));
}

void Vector::operator&=(Vector const& other) {
  COMPARAISON_VECTOR_BITWISE_HEADER;
  COMPARAISON_VARIABLE_HEADER;

  int16_t i;
  #pragma omp parallel for schedule(static) shared(this_blocks, other_blocks)
  for (i = 0; i < height; i++)
    this_blocks[i] &= other_blocks[i];
}

void Vector::operator&=(const bool bit) {
  if (!bit)
    memset(blocks, 0, height * sizeof(uint8_t));
}


/*
multiplications
*/


void Matrice::operator*=(Matrice const& other) {
  assert(height == width); //check if dimensions are compatible
  assert(other.height == other.width);

  *this = (*this) * other;
}

void Vector::operator*=(Matrice const& other) {
  assert(other.height == other.width); //check if dimensions are compatible

  *this =  other * (*this);
}
