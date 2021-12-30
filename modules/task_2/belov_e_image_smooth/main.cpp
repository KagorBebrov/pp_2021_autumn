// Copyright 2021 Belov Egor
#include <gtest/gtest.h>

#include <gtest-mpi-listener.hpp>

#include "./image_smooth.h"

TEST(Parallel_Smoothing_Filter, size_100x100_rad_1) {
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  std::vector<std::vector<float>> matr;
  const int n = 100, m = 100;
  std::vector<std::vector<float>> psmooth, smooth;
  if (rank == 0) {
    matr = Matrix(n, m);
    smooth = Smooth(matr, 1);
  }
  psmooth = ParSmooth(matr, 1);
  if (rank == 0) {
    ASSERT_EQ(smooth, psmooth);
  }
}

TEST(Parallel_Smoothing_Filter, size_150x300_rad_1) {
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  std::vector<std::vector<float>> matr;
  const int n = 150, m = 300;
  std::vector<std::vector<float>> psmooth, smooth;
  if (rank == 0) {
    matr = Matrix(n, m);
    smooth = Smooth(matr, 1);
  }
  psmooth = ParSmooth(matr, 1);
  if (rank == 0) {
    ASSERT_EQ(smooth, psmooth);
  }
}

TEST(Parallel_Smoothing_Filter, size_300x150_rad_1) {
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  std::vector<std::vector<float>> matr;
  const int n = 300, m = 150;
  std::vector<std::vector<float>> psmooth, smooth;
  if (rank == 0) {
    matr = Matrix(n, m);
    smooth = Smooth(matr, 1);
  }
  psmooth = ParSmooth(matr, 1);
  if (rank == 0) {
    ASSERT_EQ(smooth, psmooth);
  }
}

TEST(Parallel_Smoothing_Filter, size_200x200_rad_5) {
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  std::vector<std::vector<float>> matr;
  const int n = 200, m = 200;
  std::vector<std::vector<float>> psmooth, smooth;
  if (rank == 0) {
    matr = Matrix(n, m);
    smooth = Smooth(matr, 5);
  }
  psmooth = ParSmooth(matr, 5);
  if (rank == 0) {
    ASSERT_EQ(smooth, psmooth);
  }
}

TEST(Parallel_Smoothing_Filter, size_300x300_rad_5) {
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  std::vector<std::vector<float>> matr;
  const int n = 300, m = 300;
  std::vector<std::vector<float>> psmooth, smooth;
  if (rank == 0) {
    matr = Matrix(n, m);
    smooth = Smooth(matr, 5);
  }
  psmooth = ParSmooth(matr, 5);
  if (rank == 0) {
    ASSERT_EQ(smooth, psmooth);
  }
} /**/

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
