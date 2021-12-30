// Copyright 2021 Belov Egor
#include "../../../modules/task_3/belov_e_radix_merge_sort/radix_merge_sort.h"

#include <mpi.h>

#include <vector>
#include <algorithm>
#include <cmath>
#include <queue>
#include <random>

std::vector<double> CreateVector(int size) {
  std::mt19937 gen(121);
  std::vector<double> vec(size);
  for (int i = 0; i < size; i++) {
    vec[i] = gen() % 10000000 / 100.0;
  }
  return vec;
}

std::vector<double> RadixSort(const std::vector<double>& vec) {
  std::vector<double> res = vec;
  double max = *std::max_element(vec.begin(), vec.end());
  max *= 100.0;
  max = static_cast<int>(max);
  int rank = 0;
  while (max > 9) {
    rank++;
    max /= 10;
  }
  for (int i = 0; i <= rank; ++i) {
    std::vector<std::queue<double>> vect(10);
    for (std::vector<double>::iterator it = (&res)->begin();
         it != (&res)->end(); ++it) {
      int p = pow(10, i);
      vect[((static_cast<int>(*it * 100)) / p) % 10].push(*it);
    }
    int count = 0;
    for (std::vector<double>::size_type j = 0; j < res.size();) {
      while (!vect[count].empty()) {
        res[j] = vect[count].front();
        vect[count].pop();
        ++j;
      }
      ++count;
    }
  }
  return res;
}

std::vector<double> MergeSort(const std::vector<double>& First,
                              const std::vector<double>& Second) {
  std::vector<double> res(First.size() + Second.size());
  std::vector<double>::size_type first = 0, second = 0, tmp = 0;
  while (first < First.size() && second < Second.size()) {
    if (First[first] < Second[second]) {
      res[tmp] = First[first];
      tmp++;
      first++;
    } else {
      res[tmp] = Second[second];
      tmp++;
      second++;
    }
  }
  while (first < First.size()) {
    res[tmp] = First[first];
    tmp++;
    first++;
  }
  while (second < Second.size()) {
    res[tmp] = Second[second];
    tmp++;
    second++;
  }
  return res;
}

std::vector<double> PSort(const std::vector<double>& vec,
                          const std::vector<double>::size_type n) {
  int size, rank;
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  int mod = n / size;
  int div = n % size;
  std::vector<double> subres(mod), res;
  MPI_Scatter(vec.data(), mod, MPI_DOUBLE, subres.data(), mod, MPI_DOUBLE, 0,
              MPI_COMM_WORLD);
  subres = RadixSort(subres);
  if (rank != 0) {
    MPI_Send(subres.data(), mod, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
  } else {
    res = subres;
    for (int i = 1; i < size; ++i) {
      MPI_Recv(subres.data(), mod, MPI_DOUBLE, i, 0, MPI_COMM_WORLD,
               MPI_STATUSES_IGNORE);
      res = MergeSort(res, subres);
    }
    if (div) {
      subres = std::vector<double>(vec.end() - div, vec.end());
      subres = RadixSort(subres);

      res = MergeSort(res, subres);
    }
  }
  return res;
}
