#include <algorithm>
#include <vector>

template <typename T>
void process(const std::vector<T>& data) {
    uint64_t cnt = 0;
    for (auto i : data) {
        if (i > 0) {
            ++n;
        }
    }
    std::vector<T> filtered(n);
    std::copy_if(
            data.begin(),
            data.end(),
            filtered.begin(),
            [](const T& x) {return x > 0;});
    print_results(filtered.begin(), filtered.end());
}
