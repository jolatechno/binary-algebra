/*
zero initializer
*/


void reference_arithmetic::zero(Matrice mat) const {
  int16_t i, j;
  for (i = 0; i < mat.height * 8; i++)
    for (j = 0; j < mat.width * 8; j++)
      mat.write(i, j, false);
}

void reference_arithmetic::zero(Vector vect) const {
  for (int16_t i = 0; i < vect.height * 8; i++)
    vect.write(i, false);
}


/*
diagonal initializers
*/


void reference_arithmetic::diag(Matrice& mat) const {
  assert(mat.height == mat.width); //checking dimensions

  int16_t i, j;
  for (i = 0; i < mat.height * 8; i++)
    for (j = 0; j < mat.width * 8; j++)
      if (i == j) {
        mat.write(i, j, true);
      } else {
        mat.write(i, j, false);
      }
}

void reference_arithmetic::diag(Matrice& mat, const Vector diagonal) const {
  assert(mat.height == mat.width); //checking dimensions
  assert(mat.height == diagonal.height);

  int16_t i, j;
  for (i = 0; i < mat.height * 8; i++)
    for (j = 0; j < mat.width * 8; j++)
      if (i == j) {
        mat.write(i, j, diagonal[i]);
      } else {
        mat.write(i, j, false);
      }
}
