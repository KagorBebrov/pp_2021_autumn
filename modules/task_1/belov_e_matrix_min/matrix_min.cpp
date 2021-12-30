// Copyright 2021 Belov Egor
#include "../../../modules/task_1/belov_e_matrix_min/matrix_min.h"

#include <mpi.h>

#include <vector>
#include <random>

std::vector<int> Matrix(const size_t n, const size_t m) {
  std::random_device dev;
  std::mt19937 gen;
  std::vector<int> matrix(n * m);
  for (auto it = matrix.begin(); it != matrix.end(); ++it) {
    *it = gen() % 100;
  }
  return matrix;
}

int FindMin(std::vector<int> matrix) {
  int Min = matrix[0];
  for (auto it = matrix.begin() + 1; it != matrix.end(); ++it) {
    if (Min > *it) {
      Min = *it;
    }
  }
  return Min;
}

int PMin(std::vector<int> matrix, const size_t n, const size_t m) {
  int process, rank;
  MPI_Comm_size(MPI_COMM_WORLD, &process);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  int mod = n % process;
  int div = n / process;
  std::vector<int> matr(div * m);
  MPI_Scatter(matrix.data() + mod * m, div * m, MPI_INT, matr.data(), div * m,
             MPI_INT, 0, MPI_COMM_WORLD);
  int min = 0;
  int MIN = 0;
  min = FindMin(matr);
  MPI_Reduce(&min, &MIN, 1, MPI_INT, MPI_MIN, 0, MPI_COMM_WORLD);
  if (rank == 0) {
    if (mod) {
      matr = std::vector<int>(matrix.begin(), matrix.begin() + mod * m);
      min = FindMin(matr);
      if (MIN > min) {
        MIN = min;
      }
    }
  }
  return MIN;
}
