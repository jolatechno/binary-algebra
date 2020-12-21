#define ARITHMETIC_VARIABLE_HEADER \
  auto *res_blocks = res.blocks; \
  auto *other_blocks = other.blocks; \
  auto *this_blocks = blocks;

#define ARITHMETIC_MATRIX_BITWISE_HEADER \
  assert(height == other.height); \
  assert(width == other.width); \
  Matrix res(height, width); \
  auto _width = width; \
  auto _height = height; \
  auto _size = _height * _width;

#define ARITHMETIC_VECTOR_BITWISE_HEADER \
  assert(height == other.height); \
  Vector res(height); \
  auto _height = height; \
  uint64_t *res_blocks = (uint64_t *)&res.blocks[0]; \
  uint64_t *other_blocks = (uint64_t *)&other.blocks[0]; \
  uint64_t *this_blocks = (uint64_t *)&blocks[0];

#define GPU_LIMIT_2D 500;
#define CPU_LIMIT_2D 100



/*
transposition
*/


Matrix Matrix::T() const {
  Matrix res(width, height);

  uint64_t *this_blocks = blocks;
  uint64_t *res_blocks = res.blocks;

  uint16_t _width = width;
  uint16_t _height = height;

  int16_t i, j;
  _OPENMP_GPU_PRAGMA("omp parallel for schedule(static) collapse(2) shared(this_blocks, res_blocks)", \
    "omp target teams distribute parallel for collapse(2) map(to:this_blocks[:_width * _height]) map(from:res_blocks[:_width * _height])")
  for (i = 0; i < _height; i++)
    for (j = 0; j < _width; j++)
      res_blocks[i + j*_height] = transpose_block(this_blocks[j + i*_width]);

  return res;
}


/*
negation
*/


Matrix Matrix::operator~() const {
  Matrix res(height, width);

  uint64_t *this_blocks = blocks;
  uint64_t *res_blocks = res.blocks;

  uint16_t _size = width * height;

  int16_t n;
  _OPENMP_GPU_PRAGMA("omp parallel for schedule(static) shared(this_blocks, res_blocks)", \
    "omp target teams distribute parallel for map(to:this_blocks[:_size]) map(from:res_blocks[:_size])")
  for (n = 0; n < _size; n++)
    res_blocks[n] = ~this_blocks[n];

  return res;
}

Vector Vector::operator~() const {
  Vector res(height);

  uint64_t *this_blocks = (uint64_t *)&blocks[0];
  uint64_t *res_blocks = (uint64_t *)&res.blocks[0];

  uint16_t _height = height;

  int16_t i;
  _OPENMP_GPU_PRAGMA("omp parallel for schedule(static) shared(this_blocks, res_blocks)", \
    "omp target teams distribute parallel for map(to:this_blocks[:_height]) map(from:res_blocks[:_height])")
  for (i = 0; i < _height/8; i++)
    res_blocks[i] = ~this_blocks[i];

  for (i = height - height%8; i < _height; i++)
    res.blocks[i] = ~blocks[i];

  return res;
}


/*
additions
*/


Matrix Matrix::operator^(Matrix const& other) const {
  ARITHMETIC_MATRIX_BITWISE_HEADER;
  ARITHMETIC_VARIABLE_HEADER;

  int16_t n;
  _OPENMP_GPU_PRAGMA("omp parallel for schedule(static) shared(this_blocks, res_blocks, other_blocks)", \
    "omp target teams distribute parallel for map(to:this_blocks[:_size], other_blocks[:_size]) map(from:res_blocks[:_size])")
  for (n = 0; n < _height * _width; n++)
    res_blocks[n] = this_blocks[n] ^ other_blocks[n];

  return res;
}

Matrix Matrix::operator+(Matrix const& other) const {
  return *this ^ other;
}

Matrix Matrix::operator-(Matrix const& other) const {
  return *this ^ other;
}

Matrix Matrix::operator^(const bool bit) const {
  return bit ? ~(*this) : *this ;
}

Matrix Matrix::operator+(const bool bit) const {
  return *this ^ bit;
}

Matrix Matrix::operator-(const bool bit) const {
  return *this ^ bit;
}

Vector Vector::operator^(Vector const& other) const {
  ARITHMETIC_VECTOR_BITWISE_HEADER;

  int16_t i;
  _OPENMP_GPU_PRAGMA("omp parallel for schedule(static) shared(this_blocks, res_blocks, other_blocks)", \
    "omp target teams distribute parallel for map(to:this_blocks[:_height], other_blocks[:_height]) map(from:res_blocks[:_height])")
  for (i = 0; i < _height/8; i++)
    res_blocks[i] = this_blocks[i] ^ other_blocks[i];

  for (i = _height - _height%8; i < _height; i++)
    res.blocks[i] = blocks[i] ^ other.blocks[i];

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


Matrix Matrix::operator&(Matrix const& other) const {
  ARITHMETIC_MATRIX_BITWISE_HEADER;
  ARITHMETIC_VARIABLE_HEADER;

  int16_t n;
  _OPENMP_GPU_PRAGMA("omp parallel for schedule(static) shared(this_blocks, res_blocks, other_blocks)", \
    "omp target teams distribute parallel for map(to:this_blocks[:_size], other_blocks[:_size]) map(from:res_blocks[:_size])")
  for (n = 0; n < _size; n++)
    res_blocks[n] = this_blocks[n] & other_blocks[n];

  return res;
}

Matrix Matrix::operator&(const bool bit) const {
  return bit ? *this : Matrix(height, width);
}

Vector Vector::operator&(Vector const& other) const {
  ARITHMETIC_VECTOR_BITWISE_HEADER;

  int16_t i;
  _OPENMP_GPU_PRAGMA("omp parallel for schedule(static) shared(this_blocks, res_blocks, other_blocks)", \
    "omp target teams distribute parallel for map(to:this_blocks[:_height], other_blocks[:_height]) map(from:res_blocks[:_height])")
  for (i = 0; i < _height/8; i++)
    res_blocks[i] = this_blocks[i] & other_blocks[i];

  for (i = _height - _height%8; i < _height; i++)
    res.blocks[i] = blocks[i] & other.blocks[i];

  return res;
}

Vector Vector::operator&(const bool bit) const {
  return bit ? *this : Vector(height);
}


/*
multiplications
*/


Matrix Matrix::operator*(Matrix const& other) const {
  assert(width == other.height); //check if dimensions are compatible

  Matrix res(height, other.width);

  int16_t _width = width;
  int16_t _height = height;
  int16_t _size = other.width;

  ARITHMETIC_VARIABLE_HEADER;

  int16_t i, j, k;
  _OPENMP_GPU_PRAGMA("omp parallel for collapse(3) schedule(static) shared(other_blocks, res_blocks, this_blocks)", \
    "omp target teams distribute parallel for collapse(3) map(to:this_blocks[:_width * _height], other_blocks[:_width * _size]) map(from:res_blocks[:_height * _size])")
  for (j = 0; j < _size; j++)
    for (k = 0; k < _width; k++)
      for (i = 0; i < _height; i++)
        utils->_atomic_xor_fetch_64(res_blocks[i + j*_height], multiply_block_block(this_blocks[k + j*_width], other_blocks[i + k*_size]));

  return res;
}

Vector Matrix::operator*(Vector const& other) const {
  assert(width == other.height); //check if dimensions are compatible

  Vector res(height);

  int16_t _width = width;
  int16_t _height = height;

  ARITHMETIC_VARIABLE_HEADER;

  int16_t i, k;
  _OPENMP_GPU_PRAGMA("omp parallel for collapse(2) schedule(static) shared(other_blocks, res_blocks, this_blocks)", \
    "omp target teams distribute parallel for collapse(2) map(to:this_blocks[:_width * _height], other_blocks[:_width]) map(from:res_blocks[:_height])")
  for (k = 0; k < _width; k++)
    for (i = 0; i < _height; i++)
      utils->_atomic_xor_fetch_8(res_blocks[i], multiply_block_byte(this_blocks[k + i*_width], other_blocks[k]));

  return res;
}

Matrix Vector::operator*(Vector const& other) const {
  Matrix res(other.height, height);

  int16_t _height = other.height;
  int16_t _width = height;

  ARITHMETIC_VARIABLE_HEADER;

  int16_t i, j;
  _OPENMP_GPU_PRAGMA("omp parallel for collapse(2) schedule(static) shared(other_blocks, res_blocks, this_blocks)", \
    "omp target teams distribute parallel for collapse(2) map(to:this_blocks[:_width], other_blocks[:_height]) map(from:res_blocks[:_height * _width])")
  for (j = 0; j < _width; j++)
    for (i = 0; i < _height; i++)
      utils->_atomic_xor_fetch_64(res_blocks[j + i*_width], multiply_byte_byte(this_blocks[j], other_blocks[i]));

  return res;
}


/*
scalar products
*/


bool Matrix::operator%(Matrix const& other) const {
  COMPARAISON_MATRIX_BITWISE_HEADER;
  COMPARAISON_VARIABLE_HEADER;

  uint64_t sum = 0;

  int16_t n;
  _OPENMP_GPU_PRAGMA("omp parallel for reduction(^ : sum) schedule(static) shared(this_blocks, other_blocks)", \
    "omp target teams distribute parallel for map(tofrom:sum) map(to:this_blocks[:_size], other_blocks[:_size])")
  for (n = 0; n < _size; n++)
    utils->_atomic_xor_fetch_64(sum, this_blocks[n] & other_blocks[n]);

  return utils->count_ones_64(sum) % 2;
}

bool Vector::operator%(Vector const& other) const {
  COMPARAISON_VECTOR_BITWISE_HEADER;
  COMPARAISON_VARIABLE_HEADER;

  uint8_t sum = 0x00;

  int16_t i;
  _OPENMP_GPU_PRAGMA("omp parallel for reduction(^ : sum) schedule(static) shared(this_blocks, other_blocks)", \
    "omp target teams distribute parallel for map(tofrom:sum) map(to:this_blocks[:_height], other_blocks[:_height])")
  for (i = 0; i < _height; i++)
    utils->_atomic_xor_fetch_8(sum, this_blocks[i] & other_blocks[i]);

  return utils->count_ones_8(sum) % 2;
}

int Matrix::operator/(Matrix const& other) const {
  COMPARAISON_MATRIX_BITWISE_HEADER;
  COMPARAISON_VARIABLE_HEADER;

  int sum = 0;

  int16_t n;
  _OPENMP_GPU_PRAGMA("omp parallel for reduction(+ : sum) schedule(static) shared(this_blocks, other_blocks)", \
    "omp target teams distribute parallel for  map(tofrom:sum) reduction(+ : sum) map(to:this_blocks[:_size], other_blocks[:_size])")
  for (n = 0; n < _size; n++)
    sum += utils->count_ones_64(this_blocks[n] & other_blocks[n]);

  return sum;
}

int Vector::operator/(Vector const& other) const {
  COMPARAISON_VECTOR_BITWISE_HEADER;
  COMPARAISON_VARIABLE_HEADER;

  int sum = 0;

  int16_t i;
  _OPENMP_GPU_PRAGMA("omp parallel for reduction(+ : sum) schedule(static) shared(this_blocks, other_blocks)", \
    "omp target teams distribute parallel for  map(tofrom:sum) reduction(+ : sum) map(to:this_blocks[:_height], other_blocks[:_height])")
  for (i = 0; i < _height; i++)
    sum += utils->count_ones_8(this_blocks[i] & other_blocks[i]);

  return sum;
}
