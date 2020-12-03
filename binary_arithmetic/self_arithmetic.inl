/*
additions
*/


void Matrice::operator^=(Matrice const& mat) {
  if ((height != mat.height) ||
  (width != mat.width)) //check if dimensions are compatible
    throw;

  #pragma omp parallel for
  for (int16_t n = 0; n < height * width; n++)
    blocks[n] ^= mat.blocks[n];
}

void Matrice::operator^=(const bool bit) {
  if (bit) {
    #pragma omp parallel for
    for (int16_t n = 0; n < height * width; n++)
      blocks[n] = ~blocks[n];
  }
}
void Vector::operator^=(Vector const& vect) {
  if (height != vect.height) throw; //check if dimensions are compatible

  #pragma omp parallel for
  for (int16_t i = 0; i < height; i++)
    blocks[i] ^= vect.blocks[i];
}

void Vector::operator^=(const bool bit) {
  if (bit) {
    #pragma omp parallel for
    for (int16_t i = 0; i < height; i++)
      blocks[i] = ~blocks[i];
  }
}


/*
bitwise multiplications
*/


void Matrice::operator&=(Matrice const& mat) {
  if ((height != mat.height) ||
  (width != mat.width)) //check if dimensions are compatible
    throw;

  #pragma omp parallel for
  for (int16_t n = 0; n < height * width; n++)
    blocks[n] &= mat.blocks[n];
}

void Matrice::operator&=(const bool bit) {
  if (!bit)
    memset(blocks, 0, height * width * sizeof(uint64_t));
}

void Vector::operator&=(Vector const& vect) {
  if (height != vect.height) throw; //check if dimensions are compatible

  #pragma omp parallel for
  for (int16_t i = 0; i < height; i++)
    blocks[i] &= vect.blocks[i];
}

void Vector::operator&=(const bool bit) {
  if (!bit)
    memset(blocks, 0, height * sizeof(uint8_t));
}


/*
multiplications
*/


void Matrice::operator*=(Matrice const& mat) {
  if ((height != width) ||
  (mat.height != mat.width)) //check if dimensions are compatible
    throw;

  *this = (*this) * mat;
}

void Vector::operator*=(Matrice const& mat) {
  if (mat.height != mat.width) throw; //check if dimensions are compatible

  *this =  mat * (*this);
}
