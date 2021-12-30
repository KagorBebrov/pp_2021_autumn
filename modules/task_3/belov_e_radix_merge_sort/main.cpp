// Copyright 2021 Belov Egor
#include <gtest/gtest.h>

#include <gtest-mpi-listener.hpp>

#include "./radix_merge_sort.h"

TEST(Test_Parallel_Radix_Sort, Size_10) {
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  std::vector<double> vec;
  const int size = 10;
  if (rank == 0) {
    vec = CreateVector(size);
  }
  std::vector<double> PSortVec = PSort(vec, size);
  if (rank == 0) {
    std::vector<double> sortVec = RadixSort(vec);
    ASSERT_EQ(sortVec, PSortVec);
  }
}

TEST(Test_Parallel_Radix_Sort, Size_100) {
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  std::vector<double> vec;
  const int size = 100;
  if (rank == 0) {
    vec = CreateVector(size);
  }
  std::vector<double> PSortVec = PSort(vec, size);
  if (rank == 0) {
    std::vector<double> sortVec = RadixSort(vec);
    ASSERT_EQ(sortVec, PSortVec);
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
