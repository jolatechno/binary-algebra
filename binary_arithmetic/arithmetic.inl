#define ARITHMETIC_VARIABLE_HEADER \
  auto *res_blocks = res.blocks; \
  auto *other_blocks = other.blocks; \
  auto *this_blocks = blocks;

#define ARITHMETIC_MATRICE_BITWISE_HEADER \
  assert(height == other.height); \
  assert(width == other.width); \
  Matrice res(height, width); \
  auto _width = width; \
  auto _height = height;

#define ARITHMETIC_VECTOR_BITWISE_HEADER \
  assert(height == other.height); \
  Vector res(height); \
  auto _height = height;


/*
transposition
*/


Matrice Matrice::T() const {
  Matrice res(width, height);

  uint64_t *this_blocks = blocks;
  uint64_t *res_blocks = res.blocks;

  uint16_t _width = width;
  uint16_t _height = height;

  int16_t i, j;
  #pragma omp parallel for collapse(2) schedule(static) shared(this_blocks, res_blocks)
  for (i = 0; i < _height; i++)
    for (j = 0; j < _width; j++)
      res_blocks[i + j*_height] = transpose_block(this_blocks[j + i*_width]);

  return res;
}


/*
negation
*/


Matrice Matrice::operator~() const {
  Matrice res(height, width);

  uint64_t *this_blocks = blocks;
  uint64_t *res_blocks = res.blocks;

  uint16_t _size = width * height;

  #pragma omp parallel for schedule(static) shared(this_blocks, res_blocks)
  for (int16_t n = 0; n < _size; n++)
    res_blocks[n] = ~this_blocks[n];

  return res;
}

Vector Vector::operator~() const {
  Vector res(height);

  uint8_t *this_blocks = blocks;
  uint8_t *res_blocks = res.blocks;

  uint16_t _height = height;

  #pragma omp parallel for
  for (int16_t n = 0; n < _height; n++)
    res_blocks[n] = ~this_blocks[n];

  return res;
}


/*
additions
*/


Matrice Matrice::operator^(Matrice const& other) const {
  ARITHMETIC_MATRICE_BITWISE_HEADER;
  ARITHMETIC_VARIABLE_HEADER;

  #pragma omp parallel for schedule(static) shared(this_blocks, res_blocks, other_blocks)
  for (int16_t n = 0; n < _height * _width; n++)
    res_blocks[n] = this_blocks[n] ^ other_blocks[n];

  return res;
}

Matrice Matrice::operator+(Matrice const& other) const {
  return *this ^ other;
}

Matrice Matrice::operator-(Matrice const& other) const {
  return *this ^ other;
}

Matrice Matrice::operator^(const bool bit) const {
  return bit ? ~(*this) : *this ;
}

Matrice Matrice::operator+(const bool bit) const {
  return *this ^ bit;
}

Matrice Matrice::operator-(const bool bit) const {
  return *this ^ bit;
}

Vector Vector::operator^(Vector const& other) const {
  ARITHMETIC_VECTOR_BITWISE_HEADER;
  ARITHMETIC_VARIABLE_HEADER;

  #pragma omp parallel for schedule(static) shared(this_blocks, res_blocks, other_blocks)
  for (int16_t i = 0; i < _height; i++)
    res_blocks[i] = this_blocks[i] ^ other_blocks[i];

  return res;
}

Vector Vector::operator+(Vector const& other) const {
  return *this ^ other;
}

Vector Vector::operator-(Vector const& other) const {
  return *this ^ other;
}

Vector Vector::operator^(const bool bit) const {
  return bit ? ~(*this) : *this ;
}

Vector Vector::operator+(const bool bit) const {
  return *this ^ bit;
}

Vector Vector::operator-(const bool bit) const {
  return *this ^ bit;
}


/*
bitwise multiplications
*/


Matrice Matrice::operator&(Matrice const& other) const {
  ARITHMETIC_MATRICE_BITWISE_HEADER;
  ARITHMETIC_VARIABLE_HEADER;

  #pragma omp parallel for shared(this_blocks, res_blocks, other_blocks)
  for (int16_t n = 0; n < _height * _width; n++)
    res_blocks[n] = this_blocks[n] & other_blocks[n];

  return res;
}

Matrice Matrice::operator&(const bool bit) const {
  return bit ? *this : Matrice(height, width);
}

Vector Vector::operator&(Vector const& other) const {
  ARITHMETIC_VECTOR_BITWISE_HEADER;
  ARITHMETIC_VARIABLE_HEADER;

  #pragma omp parallel for shared(this_blocks, res_blocks, other_blocks)
  for (int16_t i = 0; i < _height; i++)
    res_blocks[i] = this_blocks[i] & other_blocks[i];

  return res;
}

Vector Vector::operator&(const bool bit) const {
  return bit ? *this : Vector(height);
}


/*
multiplications
*/


Matrice Matrice::operator*(Matrice const& other) const {
  assert(width == other.height); //check if dimensions are compatible

  Matrice res(height, other.width);

  int16_t _width = width;
  int16_t _height = height;
  int16_t _size = other.width;

  ARITHMETIC_VARIABLE_HEADER

  int16_t i, j;
  #pragma omp parallel for collapse(2) schedule(static) shared(other_blocks, res_blocks, this_blocks)
  for (j = 0; j < _size; j++)
    for (i = 0; i < _height; i++)
      for (int16_t k = 0; k < _width; k++)
        res_blocks[j + i*_size] ^= multiply_block_block(this_blocks[k + j*_width], other_blocks[i + k*_size]);

  return res;
}

Vector Matrice::operator*(Vector const& other) const {
  assert(width == other.height); //check if dimensions are compatible

  Vector res(height);

  int16_t _width = width;
  int16_t _height = height;

  ARITHMETIC_VARIABLE_HEADER

  int16_t i;
  #pragma omp parallel for schedule(static) shared(other_blocks, res_blocks, this_blocks)
  for (i = 0; i < _height; i++)
    for (int16_t k = 0; k < width; k++)
      res_blocks[i] ^= multiply_block_byte(this_blocks[k + i*_width], other_blocks[k]);

  return res;
}

Matrice Vector::operator*(Vector const& other) const {
  Matrice res(other.height, height);

  int16_t _height = other.height;
  int16_t _width = height;

  ARITHMETIC_VARIABLE_HEADER

  int16_t i, j;
  #pragma omp parallel for collapse(2) schedule(static) shared(other_blocks, res_blocks, this_blocks)
  for (j = 0; j < _width; j++)
    for (i = 0; i < _height; i++)
      res_blocks[j + i*_width] = multiply_byte_byte(this_blocks[j], other_blocks[i]);

  return res;
}


/*
scalar products
*/


bool Matrice::operator%(Matrice const& other) const {
  COMPARAISON_MATRICE_BITWISE_HEADER;
  COMPARAISON_VARIABLE_HEADER;

  uint64_t sum = 0;

  int16_t n;
  #pragma omp parallel for reduction(^ : sum) schedule(static) shared(this_blocks, other_blocks)
  for (n = 0; n < _height * _width; n++)
    sum ^= this_blocks[n] & other_blocks[n];

  return utils->count_ones_64(sum) % 2;
}

bool Vector::operator%(Vector const& other) const {
  COMPARAISON_VECTOR_BITWISE_HEADER;
  COMPARAISON_VARIABLE_HEADER;

  uint8_t sum = 0x00;

  int16_t i;
  #pragma omp parallel for reduction(^ : sum) schedule(static) shared(this_blocks, other_blocks)
  for (i = 0; i < _height; i++)
    sum ^= this_blocks[i] & other_blocks[i];

  return utils->count_ones_8(sum) % 2;
}

int Matrice::integer_scalar_product(Matrice const& other) const {
  COMPARAISON_MATRICE_BITWISE_HEADER;
  COMPARAISON_VARIABLE_HEADER;

  uint64_t sum = 0;

  int16_t n;
  #pragma omp parallel for reduction(+ : sum) schedule(static) shared(this_blocks, other_blocks)
  for (n = 0; n < _height * _width; n++)
    sum += utils->count_ones_64(this_blocks[n] & other_blocks[n]);

  return sum;
}

int Vector::integer_scalar_product(Vector const& other) const {
  COMPARAISON_VECTOR_BITWISE_HEADER;
  COMPARAISON_VARIABLE_HEADER;

  int sum = 0;

  int16_t i;
  #pragma omp parallel for reduction(+ : sum) schedule(static) shared(this_blocks, other_blocks)
  for (i = 0; i < _height; i++)
    sum += utils->count_ones_8(this_blocks[i] & other_blocks[i]);

  return sum;
}
