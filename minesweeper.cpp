#include<algorithm>
#include<iostream>
#include<vector>

int CheckMinesAround(const std::vector<std::vector<char>>& table, int x, int y) {
    int cnt = 0;
    int n = table.size();
    int m = table[0].size();
    for (int i = std::max(0, x - 1); i < std::min(n, x + 2); ++i) {
        for (int j = std::max(0, y - 1); j < std::min(m, y + 2); ++j) {
            if (table[i][j] == '*') {
                ++cnt;
            }
        }
    }
    return cnt;
}

int main() {
    int n, m, k;
    std::cin >> n >> m >> k;
    std::vector<std::vector<char>> table(n, std::vector<char>(m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            table[i][j] = '0';
        }
    }
    for (int i = 0; i < k; ++i) {
        int x, y;
        std::cin >> x >> y;
        table[x - 1][y - 1] = '*';
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (table[i][j] == '*') {
                continue;
            }
            table[i][j] = (CheckMinesAround(table, i, j)) + '0';
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            std::cout << table[i][j] << ' ';
        }
        std::cout << '\n';
    }
}
