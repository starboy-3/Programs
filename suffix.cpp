#include<algorithm>
#include<iostream>
#include<string>

std::string CommonSuffix(const std::string& a, const std::string& b) {
    std::string suffix;
    if (a.empty() || b.empty()) {
        return suffix;
    }
    int index1 = a.size() - 1;
    int index2 = b.size() - 1;
    for (int i = std::min(index1, index2); i >= 0; --i) {
        if (a[index1] == b[index2]) {
            suffix = a[index1] + suffix;
            --index1;
            --index2;
        } else {
            return suffix;
        }
    }
    return suffix;
}
