#include <iostream>
#include <vector>

using std::vector;

class Minesweeper {
private:
  size_t M, N;
  vector<vector<int>> Table;

public:
  Minesweeper(size_t m, size_t n) {
      M = m;
      N = n;
      Table = vector<vector<int>>(m, vector<int>(n));
  }
  size_t Rows() const {
      return M;
  }
  size_t Columns() const {
      return N;
  }
  void SetMine(size_t i, size_t j) {
      Table[i][j] = -1;
  }
  int operator()(size_t i, size_t j) const {
      return Table[i][j];
  }
  void CheckForMinesAround() {
      for (size_t i = 0; i != M; ++i) {
          for (size_t j = 0; j != N; ++j) {
              if (Table[i][j] != -1) {
                  CheckForMinesAround(i, j);
              }
          }
      }
  }

private:
  void CheckForMinesAround(int x, int y) {
      int cnt = 0;
      int n = Table.size();
      int m = Table[0].size();
      for (int i = std::max(0, x - 1); i < std::min(n, x + 2); ++i) {
          for (int j = std::max(0, y - 1); j < std::min(m, y + 2); ++j) {
              if (Table[i][j] == -1) {
                  ++cnt;
              }
          }
      }
      Table[x][y] = cnt;
  }
};

std::ostream& operator<<(std::ostream& out, const Minesweeper& ms) {
    for (size_t i = 0; i != ms.Rows(); ++i) {
        for (size_t j = 0; j != ms.Columns(); ++j)
            if (ms(i, j) == -1) {
                out << '*';
            } else {
                out << ms(i, j);
            }
        out << "\n";
    }
    return out;
}
