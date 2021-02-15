#include <algorithm>
#include <iostream>
#include <set>
#include <string>
#include <sstream>
#include <vector>

std::vector<char> all_tasks(int till) {
    std::vector<char> s;
    for (int i = 65; i < (65 + till); ++i) {
        s.push_back(static_cast<char>(i));
    }
    return s;
}

int main() {
    std::string line;
    std::stringstream ss;
    while (std::getline(std::cin, line)) {
        std::stringstream ss(line);
        std::string contest;
        ss >> contest;
        std::cout << contest << ' ';
        int amount;
        ss >> amount;
        std::string first;
        ss >> first;
        if (first[0] >= 65 && first[0] <= 90) {
            std::set<char> alphatasks;
            char letter;
            char firstchar = first[0];
            alphatasks.insert(firstchar);
            std::vector<char> father = all_tasks(amount);
            while (ss >> letter) {
                alphatasks.insert(letter);
            }
            for (auto& i : father) {
                if (alphatasks.count(i) == 0) {
                    std::cout << i << ' ';
                }
            }
        } else if (first.empty()) {
            for (int i = 1; i <= amount; ++i) {
                std::cout << i << ' ';
            }
        } else {
            std::set<int> tasks;
            int num;
            tasks.insert(stoi(first));
            while (ss >> num) {
                tasks.insert(num);
            }
            for (int i = 1; i <= amount; ++i) {
                if (tasks.count(i) == 0) {
                    std::cout << i << ' ';
                }
            }
        }
        std::cout << '\n';
    }
}
