#include <ostream>
#include <stdint.h>

std::ostream& operator<<(std::ostream& os, const Vector& vect) {
  for (int16_t i = 0; i < vect.height * 8; i++)
    os << vect[i] << " ";
  return os << "\n";
}

std::ostream& operator<<(std::ostream& os, const Matrice& mat) {
  int16_t i, k, j;
  for (i = 0; i < mat.height * 8; i++) {
    for (j = 0; j < mat.width * 8; j++)
      os << mat(i, j) << " ";
    os << "\n";
  }
  return os;
}
