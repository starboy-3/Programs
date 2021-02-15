#include<algorithm>
#include <iostream>
#include <map>
#include <vector>

struct Star {
  std::string name;
  uint64_t age;
};

uint64_t median(std::vector<uint64_t>& v) {
    std::sort(v.begin(), v.end());
    int n = v.size();
    return v[n / 2];
}

std::string FindStar(const std::vector<Star>& stars) {
    std::map<std::string, uint64_t> stars_max_age;
    for (auto& star : stars) {
        stars_max_age[star.name] = std::max(stars_max_age[star.name], star.age);
    }
    std::vector<uint64_t> stars_ages;
    for (auto& star : stars_max_age) {
        stars_ages.push_back(star.second);
    }
    uint64_t age = median(stars_ages);
    std::string ans;
    for (auto& star : stars_max_age) {
        if (star.second == age) {
            ans = star.first;
            break;
        }
    }
    return ans;
}
