// Copyright 2021 Belov Egor
#ifndef MODULES_TASK_2_BELOV_E_IMAGE_SMOOTH_IMAGE_SMOOTH_H_
#define MODULES_TASK_2_BELOV_E_IMAGE_SMOOTH_IMAGE_SMOOTH_H_

#include <vector>

using std::vector;

vector<vector<float>> Matrix(const int n, const int m);
template <typename T>
T clamp(T value, T min, T max);
float calcNewPixelColor(const vector<vector<float>>& Matrix, const int rad,
                        int X, int Y);
vector<vector<float>> Smooth(const vector<vector<float>>& Matrix,
                             const int rad);
vector<vector<float>> ParSmooth(const vector<vector<float>>& Matrix,
                                const int rad);

#endif  // MODULES_TASK_2_BELOV_E_IMAGE_SMOOTH_IMAGE_SMOOTH_H_
