#include <string>
#include <vector>

std::vector<std::string> Split(const std::string& str, char delimiter) {
    std::string word;
    std::vector<std::string> split;
    for (size_t i = 0; i < str.size(); ++i) {
        if (str[i] != delimiter) {
            word += str[i];
        } else {
            split.push_back(word);
            word = "";
        }
    }
    split.push_back(word);
    return split;
}
