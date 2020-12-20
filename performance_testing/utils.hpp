#include <chrono>
#include <stdio.h>

#include "../src/binary_arithmetic.hpp"

using namespace std::chrono;

void timeit(void (*f)(Matrix, Vector), const char* message, int iterations, const int sizes[], int n_sizes) {
  for (int size = 0; size < n_sizes; size++) {
    //initializing matrices
    Matrix mat(sizes[size], sizes[size]); Vector vect(sizes[size]);
    mat.randomize(); vect.randomize();

    //reading initial time
    auto start = high_resolution_clock::now();

    for (int i = 0; i < iterations; i++)
      (*f)(mat, vect);

    //reading end time
    auto stop = high_resolution_clock::now();
    double duration = duration_cast<nanoseconds>(stop - start).count()/iterations;

    //printing message
    if (duration < 1000) {
      printf(message, duration, "ns/op", 8*sizes[size]);
    } else if (duration < 1000000) {
      duration /= 1000;
      printf(message, duration, "µs/op", 8*sizes[size]);
    } else if (duration < 1000000000) {
      duration /= 1000000;
      printf(message, duration, "ms/op", 8*sizes[size]);
    } else {
      duration /= 1000000000;
      printf(message, duration, "s/op", 8*sizes[size]);
    }
  }
}

void timeit(void (*f)(Matrix, Matrix), const char* message, int iterations, const int sizes[], int n_sizes) {
  for (int size = 0; size < n_sizes; size++) {
    //initializing matrices
    Matrix mat1(sizes[size], sizes[size]); Matrix mat2(sizes[size], sizes[size]);
    mat1.randomize(); mat2.randomize();

    //reading initial time
    auto start = high_resolution_clock::now();

    for (int i = 0; i < iterations; i++)
      (*f)(mat1, mat2);

    //reading end time
    auto stop = high_resolution_clock::now();
    double duration = duration_cast<nanoseconds>(stop - start).count()/iterations;

    //printing message
    if (duration < 1000) {
      printf(message, duration, "ns/op", 8*sizes[size]);
    } else if (duration < 1000000) {
      duration /= 1000;
      printf(message, duration, "µs/op", 8*sizes[size]);
    } else if (duration < 1000000000) {
      duration /= 1000000;
      printf(message, duration, "ms/op", 8*sizes[size]);
    } else {
      duration /= 1000000000;
      printf(message, duration, "s/op", 8*sizes[size]);
    }

  }
}

void timeit(void (*f)(Matrix), const char* message, int iterations, const int sizes[], int n_sizes) {
  for (int size = 0; size < n_sizes; size++) {
    //initializing matrices
    Matrix mat(sizes[size], sizes[size]);
    mat.randomize();

    //reading initial time
    auto start = high_resolution_clock::now();

    for (int i = 0; i < iterations; i++)
      (*f)(mat);

    //reading end time
    auto stop = high_resolution_clock::now();
    double duration = duration_cast<nanoseconds>(stop - start).count()/iterations;

    //printing message
    if (duration < 1000) {
      printf(message, duration, "ns/op", 8*sizes[size]);
    } else if (duration < 1000000) {
      duration /= 1000;
      printf(message, duration, "µs/op", 8*sizes[size]);
    } else if (duration < 1000000000) {
      duration /= 1000000;
      printf(message, duration, "ms/op", 8*sizes[size]);
    } else {
      duration /= 1000000000;
      printf(message, duration, "s/op", 8*sizes[size]);
    }
  }
}

void timeit(void (*f)(Vector, Vector), const char* message, int iterations, const int sizes[], int n_sizes) {
  for (int size = 0; size < n_sizes; size++) {
    //initializing matrices
    Vector vect1(sizes[size]); Vector vect2(sizes[size]);
    vect1.randomize(); vect2.randomize();

    //reading initial time
    auto start = high_resolution_clock::now();

    for (int i = 0; i < iterations; i++)
      (*f)(vect1, vect2);

    //reading end time
    auto stop = high_resolution_clock::now();
    double duration = duration_cast<nanoseconds>(stop - start).count()/iterations;

    //printing message
    if (duration < 1000) {
      printf(message, duration, "ns/op", 8*sizes[size]);
    } else if (duration < 1000000) {
      duration /= 1000;
      printf(message, duration, "µs/op", 8*sizes[size]);
    } else if (duration < 1000000000) {
      duration /= 1000000;
      printf(message, duration, "ms/op", 8*sizes[size]);
    } else {
      duration /= 1000000000;
      printf(message, duration, "s/op", 8*sizes[size]);
    }
  }
}

void timeit(void (*f)(Vector), const char* message, int iterations, const int sizes[], int n_sizes) {
  for (int size = 0; size < n_sizes; size++) {
    //initializing matrices
    Vector vect(sizes[size]);
    vect.randomize();

    //reading initial time
    auto start = high_resolution_clock::now();

    for (int i = 0; i < iterations; i++)
      (*f)(vect);

    //reading end time
    auto stop = high_resolution_clock::now();
    double duration = duration_cast<nanoseconds>(stop - start).count()/iterations;

    //printing message
    if (duration < 1000) {
      printf(message, duration, "ns/op", 8*sizes[size]);
    } else if (duration < 1000000) {
      duration /= 1000;
      printf(message, duration, "µs/op", 8*sizes[size]);
    } else if (duration < 1000000000) {
      duration /= 1000000;
      printf(message, duration, "ms/op", 8*sizes[size]);
    } else {
      duration /= 1000000000;
      printf(message, duration, "s/op", 8*sizes[size]);
    }
  }
}
