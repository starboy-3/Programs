#include<iostream>
#include<vector>

int main() {
    int n, m, k;
    std::cin >> n >> m;
    std::vector<std::vector<bool>> is_empty(n, std::vector<bool>(m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            bool empty;
            std::cin >> empty;
            is_empty[i][j] = empty;
        }
    }
    std::cin >> k;
    for (int i = 0; i < n; ++i) {
        int seq = is_empty[i].front() == 0 ? 1 : 0;
        int maxempty = is_empty[i].front() == 0 ? 1 : 0;
        for (int j = 1; j < n; ++j) {
            if (is_empty[i][j] == 0) {
                ++seq;
            } else if (is_empty[i][j - 1] == 0) {
                maxempty = std::max(maxempty, seq);
                seq = 0;
            }
        }
        maxempty = std::max(maxempty, seq);
        if (maxempty >= k) {
            std::cout << i + 1 << '\n';
            return 0;
        }
    }
    std::cout << 0 << '\n';
}
