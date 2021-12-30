// Copyright 2021 Belov Egor
#ifndef MODULES_TASK_3_BELOV_E_RADIX_MERGE_SORT_RADIX_MERGE_SORT_H_
#define MODULES_TASK_3_BELOV_E_RADIX_MERGE_SORT_RADIX_MERGE_SORT_H_

#include <vector>

std::vector<double> CreateVector(int size);
std::vector<double> PSort(const std::vector<double>& vec,
                          const std::vector<double>::size_type n);
std::vector<double> RadixSort(const std::vector<double>& vec);

#endif  // MODULES_TASK_3_BELOV_E_RADIX_MERGE_SORT_RADIX_MERGE_SORT_H_
