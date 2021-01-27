#include<vector>

std::vector<int> Range(const std::vector<int>& v, size_t start, size_t end, size_t step = 1) {
    std::vector<int> range;
    if (start < v.size()) {
        end = (end > v.size()) ? v.size() : end;
        if (step > (v.size() - 1 - start)) {
            range.push_back(v[start]);
        } else if (start < end) {
            for (size_t i = start; i < end; i += step) {
                range.push_back(v[i]);
            }
        }
        return range;
    }
    return range;
}
