// Copyright 2021 Belov Egor
#include "../../../modules/task_2/belov_e_image_smooth/image_smooth.h"

#include <mpi.h>

#include <algorithm>
#include <ctime>
#include <random>

vector<vector<float>> Matrix(const int n, const int m) {
  std::vector<vector<float>> color(n);
  std::mt19937 gen(time(0));
  std::uniform_real_distribution<> urd(0, 1);
  for (int i = 0; i < n; ++i) {
    color[i] = vector<float>(m);
    for (int j = 0; j < m; ++j) color[i][j] = urd(gen);
  }
  return color;
}

template <typename T>
T clamp(T value, T min, T max) {
  if (value > max)
    return max;
  else if (value < min)
    return min;
  return value;
}

float calcNewPixelColor(const vector<vector<float>>& Matrix, const int rad,
                        int X, int Y) {
  int size = 2 * rad + 1;
  vector<float> vec(size * size);

  int index = 0;
  for (int i = -rad; i <= rad; i++)
    for (int j = -rad; j <= rad; j++) {
      float color = Matrix[clamp<int>(X + j, 0, Matrix.size() - 1)]
                          [clamp<int>(Y + i, 0, Matrix[0].size() - 1)];
      vec[index] = color;
      index += 1;
    }
  std::sort(vec.data(), vec.data() + size * size);
  return clamp<float>(vec[(size * size) / 2], 0, 1);
}

vector<vector<float>> Smooth(const vector<vector<float>>& Matrix,
                             const int rad) {
  int n = Matrix.size(), m = Matrix[0].size();
  vector<vector<float>> res(n);

  for (int x = 0; x < n; ++x) {
    res[x] = vector<float>(m);
    for (int y = 0; y < m; ++y)
      res[x][y] = calcNewPixelColor(Matrix, rad, x, y);
  }
  return res;
}

vector<vector<float>> ParSmooth(const vector<vector<float>>& Matrix,
                                const int rad) {
  int N = 0, M = 0;
  int mod = 0, div = 0;
  int r = 0;
  vector<vector<float>> matr, res;
  int proc, rank;
  MPI_Comm_size(MPI_COMM_WORLD, &proc);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  if (rank == 0) {
    N = Matrix.size();
    M = Matrix[0].size();
    r = rad;
    res.resize(N);
    for (int i = 0; i < N; ++i) res[i] = vector<float>(M);
    int size = 2 * r + 1;
    int k = N % size;
    int l = N / size;
    mod = (l % proc) * size + k;
    div = (l / proc) * size;
    for (int i = 1; i < proc; ++i) {
      int vec = mod + (div * i) - r;
      int tmp = mod + (div * i) + div + r;
      if (tmp > N) tmp = N;
      for (int j = vec; j < tmp; ++j)
        MPI_Send(Matrix[j].data(), M, MPI_FLOAT, i, 0, MPI_COMM_WORLD);
    }
  }
  MPI_Bcast(&M, 1, MPI_INT, 0, MPI_COMM_WORLD);
  MPI_Bcast(&div, 1, MPI_INT, 0, MPI_COMM_WORLD);
  MPI_Bcast(&r, 1, MPI_INT, 0, MPI_COMM_WORLD);
  MPI_Status status;
  if (rank != 0) {
    if (rank == proc - 1) {
      div += r;
    } else {
      div += 2 * r;
    }
    matr.resize(div);
    for (int i = 0; i < div; ++i) {
      matr[i] = vector<float>(M);
      MPI_Recv(matr[i].data(), M, MPI_FLOAT, 0, MPI_ANY_TAG, MPI_COMM_WORLD,
               &status);
    }
    matr = Smooth(matr, r);
    if (rank != proc - 1) {
      div -= r;
    }
    for (int i = r; i < div; ++i)
      MPI_Send(matr[i].data(), M, MPI_FLOAT, 0, 0, MPI_COMM_WORLD);
  } else {
    if (proc != 1) {
      matr =
          vector<vector<float>>(Matrix.begin(), Matrix.begin() + div + mod + r);
    } else {
      matr = vector<vector<float>>(Matrix.begin(), Matrix.begin() + div + mod);
    }
    matr = Smooth(matr, r);
    for (int i = 0; i < mod + div; ++i) res[i] = matr[i];
    for (int i = 1; i < proc; ++i)
      for (int j = (mod + div * i); j < ((mod + div * i) + div); ++j)
        MPI_Recv(res[j].data(), M, MPI_FLOAT, i, MPI_ANY_TAG, MPI_COMM_WORLD,
                 &status);
  }
  return res;
}
