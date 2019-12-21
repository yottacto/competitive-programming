// ml:run = $bin < input
#include <bits/stdc++.h>

int n;
std::vector<int> a;

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

    std::cin >> n;
    a.resize(n);
    for (auto i = 0; i < n; i++)
        std::cin >> a[i];

    auto res = 0;
    std::set<int> prev;
    std::set<int> next;
    next.emplace(a[0] + 1);
    for (auto i = 0; i < n; i++) {
        std::swap(prev, next);
        next.clear();
        auto p = 0;
        std::cout << prev.size() << ": ";
        for (auto c : prev)
            std::cout << c << " ";
        std::cout << "\n";
        for (auto c : prev) {
            if (c <= a[i]) {
                auto d = c - p - 1;
                res++;
                if (d & 1)
                    next.emplace(p + 1);
                res += d / 2;
            } else {
                auto d = a[i] - p;
                if (!d)
                    break;
                if (d & 1)
                    next.emplace(p + 1);
                res += d / 2;
                break;
            }
            p = c;
        }
        if (i + 1 < n)
            next.emplace(a[i + 1] + 1);
    }
    std::cout << res << "\n";
}

