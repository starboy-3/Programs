#include <vector>

std::vector<std::vector<int>> Transpose(const std::vector<std::vector<int>>& matrix) {
  std::vector<std::vector<int>> transposed(matrix[0].size(), std::vector<int>(matrix.size()));

  for (size_t i = 0; i < matrix[0].size(); ++i) {
    for (size_t j = 0; j < matrix.size(); ++j) {
      transposed[i][j] = matrix[j][i];
    }
  }
  return transposed;
}
