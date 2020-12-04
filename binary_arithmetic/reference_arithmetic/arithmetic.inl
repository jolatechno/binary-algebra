/*
transposition
*/


Matrice reference_arithmetic::transpose(Matrice const& mat) const {
  Matrice transposed(mat.width, mat.height);

  uint16_t i, j;
  for (i = 0; i < mat.height * 8; i++)
    for (j = 0; j < mat.width * 8; j++)
      transposed.write(j, i, mat(i, j));

  return transposed;
}

/*
multiplications
*/

Matrice reference_arithmetic::multiplication(Matrice const& mat1, Matrice const& mat2) const {
  assert(mat1.width == mat2.height);

  Matrice product(mat1.height, mat2.width);

  bool sum;
  uint16_t i, j, k;
  for (i = 0; i < mat1.height * 8; i++)
    for (j = 0; j < mat2.width * 8; j++) {
      sum = 0;
      for (k = 0; k < mat1.width * 8; k++)
        sum = (sum != (mat1(i, k) && mat2(k, j)));

      product.write(i, j, sum);
    }

  return product;
}

Vector reference_arithmetic::multiplication(Matrice const& mat, Vector const& vect) const {
  assert(mat.width == vect.height);

  Vector product(mat.height);

  bool sum;
  uint16_t i, k;
  for (i = 0; i < mat.height * 8; i++) {
    sum = 0;
    for (k = 0; k < mat.width * 8; k++)
      sum = (sum != (mat(i, k) && vect[k]));

    product.write(i, sum);
  }

  return product;
}

Matrice reference_arithmetic::multiplication(Vector const& vect1, Vector const& vect2) const {
  Matrice product(vect2.height, vect1.height);

  uint16_t i, j;
  for (i = 0; i < vect2.height * 8; i++) {
    for (j = 0; j < vect1.height * 8; j++)
      product.write(i, j, vect1[j] && vect2[i]);
  }

  return product;
}


/*
additions
*/


Matrice reference_arithmetic::addition(Matrice const& mat1, Matrice const& mat2) const {
  assert(mat1.height == mat2.height); //check if dimensions are compatible
  assert(mat1.width == mat2.width);

  Matrice mat_res(mat1.height, mat1.width);

  int16_t i, j;
  for (i = 0; i < mat1.height * 8; i++)
    for (j = 0; j < mat1.width * 8; j++)
      mat_res.write(i, j, mat1(i, j) != mat2(i, j));

  return mat_res;
}

Matrice reference_arithmetic::addition(Matrice const& mat, bool bit) const {
  Matrice mat_res(mat.height, mat.width);

  int16_t i, j;
  for (i = 0; i < mat.height * 8; i++)
    for (j = 0; j < mat.width * 8; j++)
      mat_res.write(i, j, mat(i, j) != bit);

  return mat_res;
}

Vector reference_arithmetic::addition(Vector const& vect1, Vector const& vect2) const {
  assert(vect1.height == vect2.height); //check if dimensions are compatible

  Vector vect_res(vect1.height);

  for (int16_t i = 0; i < vect1.height * 8; i++)
    vect_res.write(i, vect1[i] != vect2[i]);

  return vect_res;
}

Vector reference_arithmetic::addition(Vector const& vect, bool bit) const {
  Vector vect_res(vect.height);

  for (int16_t i = 0; i < vect.height * 8; i++)
    vect_res.write(i, vect[i] != bit);

  return vect_res;
}


/*
bitwise multiplications
*/


Matrice reference_arithmetic::bitwise_multiplication(Matrice const& mat1, Matrice const& mat2) const {
  assert(mat1.height == mat2.height); //check if dimensions are compatible
  assert(mat1.width == mat2.width);

  Matrice mat_res(mat1.height, mat1.width);

  int16_t i, j;
  for (i = 0; i < mat1.height * 8; i++)
    for (j = 0; j < mat1.width * 8; j++)
      mat_res.write(i, j, mat1(i, j) && mat2(i, j));

  return mat_res;
}

Matrice reference_arithmetic::bitwise_multiplication(Matrice const& mat, bool bit) const {
  Matrice mat_res(mat.height, mat.width);

  int16_t i, j;
  for (i = 0; i < mat.height * 8; i++)
    for (j = 0; j < mat.width * 8; j++)
      mat_res.write(i, j, mat(i, j) && bit);

  return mat_res;
}

Vector reference_arithmetic::bitwise_multiplication(Vector const& vect1, Vector const& vect2) const {
  assert(vect1.height == vect2.height); //check if dimensions are compatible

  Vector vect_res(vect1.height);

  for (int16_t i = 0; i < vect1.height * 8; i++)
    vect_res.write(i, vect1[i] && vect2[i]);

  return vect_res;
}

Vector reference_arithmetic::bitwise_multiplication(Vector const& vect, bool bit) const {
  Vector vect_res(vect.height);

  for (int16_t i = 0; i < vect.height * 8; i++)
    vect_res.write(i, vect[i] && bit);

  return vect_res;
}


/*
negation
*/


Matrice reference_arithmetic::negate(Matrice const& mat) const {
  Matrice mat_res(mat.height, mat.width);

  int16_t i, j;
  for (i = 0; i < mat.height * 8; i++)
    for (j = 0; j < mat.width * 8; j++)
      mat_res.write(i, j, !mat(i, j));

  return mat_res;
}

Vector reference_arithmetic::negate(Vector const& vect) const {
  Vector vect_res(vect.height);

  for (int16_t i = 0; i < vect.height * 8; i++)
    vect_res.write(i, !vect[i]);

  return vect_res;
}


/*
scalar product
*/


bool reference_arithmetic::scalar_product(Matrice const& mat1, Matrice const& mat2) const {
  assert(mat1.height == mat2.height); //check if dimensions are compatible
  assert(mat1.width == mat2.width);

  bool sum = 0;

  int16_t i, j;
  for (i = 0; i < mat1.height * 8; i++)
    for (j = 0; j < mat1.width * 8; j++)
      sum = (sum != (mat1(i, j) && mat2(i, j)));

  return sum;
}

bool reference_arithmetic::scalar_product(Vector const& vect1, Vector const& vect2) const {
  assert(vect1.height == vect2.height); //check if dimensions are compatible

  bool sum = 0;

  for (int16_t i = 0; i < vect1.height * 8; i++)
    sum = (sum != (vect1[i] && vect2[i]));

  return sum;
}

int reference_arithmetic::integer_scalar_product(Matrice const& mat1, Matrice const& mat2) const {
  assert(mat1.height == mat2.height); //check if dimensions are compatible
  assert(mat1.width == mat2.width);

  int sum = 0;

  int16_t i, j;
  for (i = 0; i < mat1.height * 8; i++)
    for (j = 0; j < mat1.width * 8; j++)
      sum += mat1(i, j) && mat2(i, j);

  return sum;
}

int reference_arithmetic::integer_scalar_product(Vector const& vect1, Vector const& vect2) const {
  assert(vect1.height == vect2.height); //check if dimensions are compatible

  int sum = 0;

  for (int16_t i = 0; i < vect1.height * 8; i++)
    sum += vect1[i] && vect2[i];

  return sum;
}
