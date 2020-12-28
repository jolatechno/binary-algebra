/*
slices
*/


Matrix reference_arithmetic::slice(Matrix const& mat, int start_i, int start_j, int length_i, int length_j) const {
  Matrix res(length_i, length_j);

  for (int16_t i = 0; i < 8*length_i; i++)
    for (int16_t j = 0; j < 8*length_j; j++)
      res(i, j) = mat(i + 8*start_i, j + 8*start_j);

  return res;
}

Vector reference_arithmetic::slice(Vector const& vect, int start, int length) const {
  Vector res(length);

  for (int16_t i = 0; i < 8*length; i++)
      res[i] = vect[i + 8*start];

  return res;
}


/*
zero initializer
*/


void reference_arithmetic::zero(Matrix& mat) const {
  int16_t i, j;
  for (i = 0; i < mat.height * 8; i++)
    for (j = 0; j < mat.width * 8; j++)
      mat(i, j) = false;
}

void reference_arithmetic::zero(Vector& vect) const {
  for (int16_t i = 0; i < vect.height * 8; i++)
    vect[i] = false;
}


/*
diagonal initializers
*/


void reference_arithmetic::diag(Matrix& mat) const {
  assert(mat.height == mat.width); //checking dimensions

  int16_t i, j;
  for (i = 0; i < mat.height * 8; i++)
    for (j = 0; j < mat.width * 8; j++)
      if (i == j) {
        mat(i, j) = true;
      } else {
        mat(i, j) = false;
      }
}

void reference_arithmetic::diag(Matrix& mat, Vector const& diagonal) const {
  assert(mat.height == mat.width); //checking dimensions
  assert(mat.height == diagonal.height);

  int16_t i, j;
  for (i = 0; i < mat.height * 8; i++)
    for (j = 0; j < mat.width * 8; j++)
      if (i == j) {
        mat(i, j) = diagonal[i];
      } else {
        mat(i, j) = false;
      }
}
