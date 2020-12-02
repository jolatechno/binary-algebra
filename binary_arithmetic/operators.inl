/*
transposition
*/


Matrice Matrice::T() const {
  Matrice mat_t(width, height);

  #pragma omp parallel for collapse(2)
  for (int16_t i = 0; i < height; i++)
    for (int16_t j = 0; j < width; j++)
      mat_t.blocks[i + j*mat_t.width] = transpose_block(blocks[j + i*width]);

  return mat_t;
}


/*
negation
*/


Matrice Matrice::operator~() const {
  Matrice mat_res(height, width);

  #pragma omp parallel for
  for (int16_t n = 0; n < height * width; n++)
    mat_res.blocks[n] = ~blocks[n];

  return mat_res;
}

Vector Vector::operator~() const {
  Vector vect_res(height);

  #pragma omp parallel for
  for (int16_t n = 0; n < height; n++)
    vect_res.blocks[n] = ~blocks[n];

  return vect_res;
}


/*
additions
*/


Matrice Matrice::operator^(const Matrice mat) const {
  assert(height == mat.height); //check if dimensions are compatible
  assert(width == mat.width);

  Matrice mat_res(height, width);

  #pragma omp parallel for
  for (int16_t n = 0; n < height * width; n++)
    mat_res.blocks[n] = blocks[n] ^ mat.blocks[n];

  return mat_res;
}

Matrice Matrice::operator^(const bool bit) const {
  return bit ? ~(*this) : *this ;
}

Vector Vector::operator^(const Vector vect) const {
  assert(height == vect.height); //check if dimensions are compatible

  Vector vect_res(height);

  #pragma omp parallel for
  for (int16_t i = 0; i < height; i++)
    vect_res.blocks[i] = blocks[i] ^ vect.blocks[i];

  return vect_res;
}

Vector Vector::operator^(const bool bit) const {
  return bit ? ~(*this) : *this ;
}


/*
bitwise multiplications
*/


Matrice Matrice::operator&(const Matrice mat) const {
  assert(height == mat.height); //check if dimensions are compatible
  assert(width == mat.width);

  Matrice mat_res(height, width);

  #pragma omp parallel for
  for (int16_t n = 0; n < height * width; n++)
    mat_res.blocks[n] = blocks[n] & mat.blocks[n];

  return mat_res;
}

Matrice Matrice::operator&(const bool bit) const {
  return bit ? *this : Matrice(height, width);
}

Vector Vector::operator&(const Vector vect) const {
  assert(height == vect.height); //check if dimensions are compatible

  Vector vect_res(height);

  #pragma omp parallel for
  for (int16_t i = 0; i < height; i++)
    vect_res.blocks[i] = blocks[i] & vect.blocks[i];

  return vect_res;
}

Vector Vector::operator&(const bool bit) const {
  return bit ? *this : Vector(height);
}


/*
multiplications
*/


Matrice Matrice::operator*(const Matrice mat) const {
  assert(width == mat.height); //check if dimensions are compatible

  Matrice mat_res(height, mat.width);

  #pragma omp parallel for collapse(2)
  for (int16_t j = 0; j < mat_res.width; j++)
    for (int16_t i = 0; i < mat_res.height; i++) {
      uint64_t sum = 0;

      #pragma omp parallel for reduction(^ : sum)
      for (int16_t k = 0; k < mat.width; k++)
        sum ^= multiply_block_block(blocks[k + j*width], mat.blocks[i + k*mat.width]);

      mat_res.blocks[j + i*mat_res.width] = sum;
    }

  return mat_res;
}

Vector Matrice::operator*(const Vector vect) const {
  assert(width == vect.height); //check if dimensions are compatible

  Vector vect_res(height);

  #pragma omp parallel for
  for (int16_t i = 0; i < height; i++) {
    int8_t sum = 0x00;

    #pragma omp parallel for reduction(^ : sum)
    for (int16_t k = 0; k < width; k++)
      sum ^= multiply_block_byte(blocks[k + i*width], vect.blocks[k]);

    vect_res.blocks[i] = sum;
  }

  return vect_res;
}

Matrice Vector::operator*(const Vector vect) const {
  Matrice mat_res(vect.height, height);

  #pragma omp parallel for collapse(2)
  for (int16_t j = 0; j < mat_res.width; j++)
    for (int16_t i = 0; i < mat_res.height; i++)
      mat_res.blocks[j + i*mat_res.width] = multiply_byte_byte(blocks[j], vect.blocks[i]);

  return mat_res;
}


/*
scalar products
*/


bool Matrice::operator%(const Matrice mat) const {
  assert(height == mat.height); //check if dimensions are compatible
  assert(width == mat.width);

  uint64_t sum = 0;

  #pragma omp parallel for reduction(^ : sum)
  for (int16_t n = 0; n < height * width; n++)
    sum ^= blocks[n] & mat.blocks[n];

  return count_ones_64(sum);
}


bool Vector::operator%(const Vector vect) const {
  assert(height == vect.height); //check if dimensions are compatible

  uint8_t sum = 0x00;

  #pragma omp parallel for reduction(^ : sum)
  for (int16_t i = 0; i < height; i++)
    sum ^= blocks[i] & vect.blocks[i];

  return count_ones_8(sum);
}
