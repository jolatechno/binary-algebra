/*
equality between objects
*/


bool Matrice::operator==(Matrice const& mat) const {
  if ((height != mat.height) ||
  (width != mat.width)) //check if dimensions are compatible
    return false;

  bool equal_ = true;

  #pragma omp parallel
  {
    #pragma omp for
    for (int16_t n = 0; n < height * width; n++) {
      if (blocks[n] != mat.blocks[n]) {
        #pragma omp critical
        equal_ = false;
        #pragma omp cancel for
      }
      #pragma omp cancellation point for
    }
  }

  return equal_;
}

bool Vector::operator==(Vector const& vect) const {
  if (height != vect.height) return false; //check if dimensions are compatible

  bool equal_ = true;

  #pragma omp parallel
  {
    #pragma omp for
    for (int16_t i = 0; i < height; i++) {
      if (blocks[i] != vect.blocks[i]) {
        #pragma omp critical
        equal_ = false;
        #pragma omp cancel for
      }
      #pragma omp cancellation point for
    }
  }

  return equal_;
}


/*
equality with bits
*/


bool Matrice::operator==(const bool bit) const {
  bool equal_ = true;
  uint64_t target = bit ? 0xFFFFFFFFFFFFFFFF : 0;

  #pragma omp parallel
  {
    #pragma omp for
    for (int16_t n = 0; n < height * width; n++) {
      if (blocks[n] != target) {
        #pragma omp critical
        equal_ = false;
        #pragma omp cancel for
      }
      #pragma omp cancellation point for
    }
  }

  return equal_;
}

bool Vector::operator==(const bool bit) const {
  bool equal_ = true;
  uint8_t target = bit ? 0xFF : 0;

  #pragma omp parallel
  {
    #pragma omp for
    for (int16_t i = 0; i < height; i++) {
      if (blocks[i] != target) {
        #pragma omp critical
        equal_ = false;
        #pragma omp cancel for
      }
      #pragma omp cancellation point for
    }
  }

  return equal_;
}


/*
smaller than comparaisons
*/


int Matrice::difference(Matrice const& mat) const {
  assert(height == mat.height); //check if dimensions are compatible
  assert(width == mat.width);

  int diff = 0;

  #pragma omp parallel for reduction(+ : diff)
  for (int16_t n = 0; n < height * width; n++)
    diff +=  utils->count_ones_64(blocks[n]) - utils->count_ones_64(mat.blocks[n]);

  return diff;
}

int Vector::difference(Vector const& vect) const {
  assert(height == vect.height); //check if dimensions are compatible

  int diff = 0;

  #pragma omp parallel for reduction(+ : diff)
  for (int16_t i = 0; i < height; i++)
    diff +=  utils->count_ones_8(blocks[i]) - utils->count_ones_8(vect.blocks[i]);

  return diff;
}


/*
other comparaison obtained from all the above
*/


bool Matrice::operator!=(Matrice const& mat) const {
  return !(*this == mat);
}

bool Vector::operator!=(Vector const& vect) const {
  return !(*this == vect);
}

bool Matrice::operator!=(const bool bit) const {
  return !(*this == bit);
}

bool Vector::operator!=(const bool bit) const {
  return !(*this == bit);
}

bool Matrice::operator<(Matrice const& mat) const {
  return this->difference(mat) < 0;
}

bool Vector::operator<(Vector const& vect) const {
  return this->difference(vect) < 0;
}

bool Matrice::operator<(const bool bit) const {
  if (bit)
    return !(*this == true);
  return true;
}

bool Vector::operator<(const bool bit) const {
  if (bit)
    return !(*this == true);
  return true;
}

bool Matrice::operator>(Matrice const& mat) const {
  return this->difference(mat) > 0;
}

bool Vector::operator>(Vector const& vect) const {
  return this->difference(vect) > 0;
}

bool Matrice::operator>(const bool bit) const {
  if (bit)
    return false;
  return !(*this == false);
}

bool Vector::operator>(const bool bit) const {
  if (bit)
    return false;
  return !(*this == false);
}

bool Matrice::operator<=(Matrice const& mat) const {
  return this->difference(mat) <= 0;
}

bool Vector::operator<=(Vector const& vect) const {
  return this->difference(vect) <= 0;
}

bool Matrice::operator<=(const bool bit) const {
  return bit;
}

bool Vector::operator<=(const bool bit) const {
  return bit;
}

bool Matrice::operator>=(Matrice const& mat) const {
  return this->difference(mat) >= 0;
}

bool Vector::operator>=(Vector const& vect) const {
  return this->difference(vect) >= 0;
}


bool Matrice::operator>=(const bool bit) const {
  if (bit)
    return *this == true;
  return true;
}

bool Vector::operator>=(const bool bit) const {
  if (bit)
    return *this == true;
  return true;
}
