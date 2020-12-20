/*
equality between objects
*/


bool reference_arithmetic::equal(Matrix const& mat1, Matrix const& mat2) const {
  if ((mat1.width != mat2.width) ||
  (mat1.height != mat2.height)) //check if dimensions are compatible
    return false;

  uint16_t i, j;
  for (i = 0; i < mat1.height * 8; i++)
    for (j = 0; j < mat1.width * 8; j++)
      if (mat1(i, j) != mat2(i, j))
        return false;

  return true;
}

bool reference_arithmetic::equal(Vector const& vect1, Vector const& vect2) const {
  if (vect1.height != vect2.height) return false; //check if dimensions are compatible

  for (uint16_t i = 0; i < vect1.height * 8; i++)
    if (vect1[i] != vect2[i])
      return false;

  return true;
}


/*
equality between objects and bit
*/


bool reference_arithmetic::equal(Matrix const& mat1, bool bit) const {
  uint16_t i, j;
  for (i = 0; i < mat1.height * 8; i++)
    for (j = 0; j < mat1.width * 8; j++)
      if (mat1(i, j) != bit)
        return false;

  return true;
}

bool reference_arithmetic::equal(Vector const& vect, bool bit) const {
  for (uint16_t i = 0; i < vect.height * 8; i++)
    if (vect[i] != bit)
      return false;

  return true;
}


/*
other comparaisons
*/

bool reference_arithmetic::greater(Matrix const& mat1, Matrix const& mat2) const {
  return integer_scalar_product(mat1, mat1) > integer_scalar_product(mat2, mat2);
}

bool reference_arithmetic::greater(Vector const& vect1, Vector const& vect2) const {
  return integer_scalar_product(vect1, vect1) > integer_scalar_product(vect2, vect2);
}
