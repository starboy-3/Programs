#include <algorithm>
#include <iostream>
#include <tuple>
#include<vector>

struct Alarm {
  int d, h, m;
};

int main() {
    int day, minute, hour, n;
    std::cin >> day >> hour >> minute;
    std::vector<std::vector<Alarm>> week(7);
    std::cin >> n;
    for (int i = 0; i < n; ++i) {
        int dt, ht, mt;
        std::cin >> dt >> ht >> mt;
        if (dt == 0) {
            for (int j = 0; j < 7; ++j) {
                week[j].push_back({j + 1, ht, mt});
            }
            continue;
        }
        week[dt - 1].push_back({dt, ht, mt});
    }
    for (auto& c : week) {
        sort(c.begin(), c.end(), [](const Alarm& a, const Alarm& b) {
          return std::tie(a.h, a.m) < std::tie(b.h, b.m);
        });
    }
    for (int i = 0; i < 8; ++i) {
        bool iscycle = (((day + i) > 7) ? true : false);
        for (Alarm a : week[(day + i - 1) % 7]) {
            if (!iscycle && a.d == day &&
                std::tie(a.h, a.m) >= std::tie(hour, minute)) {
                std::cout << (((day + i) % 7 == 0) ? 7 : ((day + i) % 7)) << ' ' <<
                          a.h << ' ' << a.m;
                return 0;
            }
            if (!iscycle &&
                (std::tie(a.d, a.h, a.m) >= std::tie(day, hour, minute))) {
                std::cout << (((day + i) % 7 == 0) ? 7 : ((day + i) % 7)) << ' '
                          << a.h << ' ' << a.m;
                return 0;
            } else if (iscycle
                && std::tie(a.d, a.h, a.m) <= std::tie(day, hour, minute)) {
                std::cout << (((day + i) % 7 == 0) ? 7 : ((day + i) % 7)) << ' ' <<
                          a.h << ' ' << a.m << '\n';
                return 0;
            }
        }
    }
}
