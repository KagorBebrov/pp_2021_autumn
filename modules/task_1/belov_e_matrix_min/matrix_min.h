// Copyright 2021 Belov Egor
#pragma once

#ifndef MODULES_TASK_1_BELOV_E_MATRIX_MIN_MATRIX_MIN_H_
#define MODULES_TASK_1_BELOV_E_MATRIX_MIN_MATRIX_MIN_H_

#include <vector>

std::vector<int> Matrix(const size_t n, const size_t m);
int FindMin(std::vector<int> matrix);
int PMin(std::vector<int> matrix, const size_t n, const size_t m);

#endif  // MODULES_TASK_1_BELOV_E_MATRIX_MIN_MATRIX_MIN_H_
