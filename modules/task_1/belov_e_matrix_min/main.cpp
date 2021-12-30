// Copyright 2021 Belov Egor
#include <gtest/gtest.h>

#include <gtest-mpi-listener.hpp>

#include "./matrix_min.h"

TEST(Parallel_Matrix_Minimum, size_10x10) {
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  std::vector<int> matr;
  const int n = 10, m = 10;
  int pmin, min;
  if (rank == 0) {
    matr = Matrix(n, m);
    min = FindMin(matr);
  }
  pmin = PMin(matr, n, m);
  if (rank == 0) {
    ASSERT_EQ(min, pmin);
  }
}

TEST(Parallel_Matrix_Minimum, size_50x25) {
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  std::vector<int> matr;
  const int n = 50, m = 25;
  int pmin, min;
  if (rank == 0) {
    matr = Matrix(n, m);
    min = FindMin(matr);
  }
  pmin = PMin(matr, n, m);
  if (rank == 0) {
    ASSERT_EQ(min, pmin);
  }
}

TEST(Parallel_Matrix_Minimum, size50x100) {
  int runk;
  MPI_Comm_rank(MPI_COMM_WORLD, &runk);
  std::vector<int> matr;
  const int n = 50, m = 100;
  int pmin, min;
  if (runk == 0) {
    matr = Matrix(n, m);
    min = FindMin(matr);
  }
  pmin = PMin(matr, n, m);
  if (runk == 0) {
    ASSERT_EQ(min, pmin);
  }
}

TEST(Parallel_Matrix_Minimum, size300x300) {
  int runk;
  MPI_Comm_rank(MPI_COMM_WORLD, &runk);
  std::vector<int> matr;
  const int n = 300, m = 300;
  int pmin, min;
  if (runk == 0) {
    matr = Matrix(n, m);
    min = FindMin(matr);
  }
  pmin = PMin(matr, n, m);
  if (runk == 0) {
    ASSERT_EQ(min, pmin);
  }
}

TEST(Parallel_Matrix_Minimum, size1000x1000) {
  int runk;
  MPI_Comm_rank(MPI_COMM_WORLD, &runk);
  std::vector<int> matr;
  const int n = 1000, m = 1000;
  int pmin, min;
  if (runk == 0) {
    matr = Matrix(n, m);
    min = FindMin(matr);
  }
  pmin = PMin(matr, n, m);
  if (runk == 0) {
    ASSERT_EQ(min, pmin);
  }
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  MPI_Init(&argc, &argv);

  ::testing::AddGlobalTestEnvironment(new GTestMPIListener::MPIEnvironment);
  ::testing::TestEventListeners& listeners =
      ::testing::UnitTest::GetInstance()->listeners();

  listeners.Release(listeners.default_result_printer());
  listeners.Release(listeners.default_xml_generator());

  listeners.Append(new GTestMPIListener::MPIMinimalistPrinter);
  return RUN_ALL_TESTS();
}
