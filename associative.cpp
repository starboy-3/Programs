#include<iostream>
#include<vector>

int main() {
    int n;
    std::cin >> n;
    std::vector<std::vector<int>> matrix(n, std::vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int num;
            std::cin >> num;
            matrix[i][j] = num;
        }
    }
    for (int x = 0; x < n; ++x) {
        for (int y = 0; y < n; ++y) {
            for (int z = 0; z < n; ++z) {
                if (matrix[x][matrix[y][z]] != matrix[matrix[x][y]][z]) {
                    std::cout << "NO" << '\n';
                    return 0;
                }
            }
        }
    }
    std::cout << "YES" << '\n';
}
