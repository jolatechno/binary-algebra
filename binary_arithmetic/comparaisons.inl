/*
equality between objects
*/


bool Matrice::operator==(const Matrice mat) const {
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

bool Vector::operator==(const Vector vect) const {
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
inequality between objects
*/


bool Matrice::operator!=(const Matrice mat) const {
  return !(*this == mat);
}

bool Vector::operator!=(const Vector vect) const {
  return !(*this == vect);
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
